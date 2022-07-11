package Sever;

import Classes.ExamItem;
import Classes.Form;
import Classes.Instrument;
import Classes.Patient;

import java.io.IOException;
import java.net.InetSocketAddress;
import java.net.SocketException;
import java.nio.ByteBuffer;
import java.nio.CharBuffer;
import java.nio.channels.*;
import java.nio.charset.CharacterCodingException;
import java.nio.charset.Charset;
import java.nio.charset.CharsetDecoder;
import java.nio.charset.CharsetEncoder;
import java.sql.SQLException;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.HashSet;
import java.util.Iterator;

public class Server extends Thread {
    private int address;
    private int timeOut;
    private int numPatient;
    private boolean running;

    private ToolFunctions toolFuns;

    String msgInfo="###log:";

    public Server(int address, int timeOut, int numPatient) {
        this.address = address;
        this.timeOut = timeOut;
        this.numPatient = numPatient;
        running = true;
        // TODO 初始化各方法数据及查询
        try {
            toolFuns = new ToolFunctions(Integer.toString(numPatient));
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }

    public void run() {
        Selector selector = null;
        ServerSocketChannel server = null;
        int count = 0;

        try {
            // TODO 创建一个Selector
            selector = Selector.open();

            // TODO 创建Socket并注册
            server = ServerSocketChannel.open();
            server.configureBlocking(false);
            server.register(selector, SelectionKey.OP_ACCEPT);

            // TODO 启动端口监听
            InetSocketAddress ip = new InetSocketAddress(address);
            server.socket().bind(ip);

            System.out.println("$local:"+ "服务器开启");
            // TODO 监听事件
            while (running) {
                //----------------算法运行-----------------------
                // TODO 检查结束条件
                boolean flag=false;
                for(String pId:toolFuns.getDataBase().getPatients().keySet()){
                    Patient patient=toolFuns.getDataBase().getPatients().get(pId);
                    if(patient.getStatus()==-1){//只要还有人是待推荐
                        flag = true;//就继续运行
                        break;
                    }
                }
                if (flag==true){
                    // TODO 设置患者可选仪器列表并初始化未检查仪器列表
                    toolFuns.setPatCan();
                    // TODO 更新每个患者状态，时间流转
                    toolFuns.refreshForm();
                    toolFuns.addTIME();
                }else{
                    System.out.println("/********End********/");
                    running=false;//结束算法运行线程
                }
                //----------------------------------------------

                //监听事件
                selector.select(timeOut);//若1秒内无事件则刷新
                //事件来源列表
                Iterator<SelectionKey> it = selector.selectedKeys().iterator();

                while (it.hasNext()) {
                    SelectionKey key = it.next();
                    //删除该事件
                    it.remove();
                    //判断事件类型
                    if (key.isAcceptable()) {
                        ServerSocketChannel server2 = (ServerSocketChannel) key.channel();
                        SocketChannel channel = server2.accept();
                        channel.configureBlocking(false);
                        if (channel.isConnectionPending()) {
                            channel.finishConnect();
                        }
                        channel.register(selector, SelectionKey.OP_READ);//连接以后看看有没有read
                        System.out.println(msgInfo+"accept客户端：" + channel.socket().getInetAddress().getHostName()
                                + channel.socket().getPort());
                    } else if (key.isReadable()) {
                        //读取数据事件
                        SocketChannel channel = (SocketChannel) key.channel();

                        //读取数据
                        CharsetDecoder decoder = Charset.forName("UTF-8").newDecoder();
                        ByteBuffer buffer = ByteBuffer.allocate(1024);
                        channel.read(buffer);
                        buffer.flip();
                        String msg = decoder.decode(buffer).toString();


                        //-----------------数据处理-----------------
                        System.out.println(msgInfo+channel.socket().getInetAddress().getHostName()
                                + channel.socket().getPort()+" "+"收到：" + msg);
                        String msg_1 = msg;
                        String[] label = msg.split(";");
                        // TODO 查询患者信息
                        if (label[0].equals("query_patientInfo")) {
                            Patient patient = toolFuns.getDataBase().getPatients().get(label[1]);
                            //若能找到
                            if (patient != null) {
                                ExamItem examItem = toolFuns.getDataBase().getItems().get(patient.getExamining().getExamId());
                                if(examItem!=null){
                                    msg = patient.getPaId() + ";" + patient.getName()
                                            + ";" + patient.getSex() + ";" + patient.getAge()
                                            + ";" + patient.getPacChoose() + ";" + patient.getLimit() + ";" + examItem.getExamName()
                                            + ";" + toolFuns.recommend1(patient) + ";" + patient.getExamining().getFinTime();
                                    System.out.println(msgInfo+channel.socket().getInetAddress().getHostName()
                                            + channel.socket().getPort()+" "+"query found");
                                }else{
                                    msg = patient.getPaId() + ";" + patient.getName()
                                            + ";" + patient.getSex() + ";" + patient.getAge()
                                            + ";" + patient.getPacChoose() + ";" + patient.getLimit() + ";" + "no examining"
                                            + ";" + toolFuns.recommend1(patient) + ";" + "NULL";
                                    System.out.println(msgInfo+channel.socket().getInetAddress().getHostName()
                                            + channel.socket().getPort()+" "+"query found");
                                }
                            } else {
                                msg = "not found";
                                System.out.println(msgInfo+channel.socket().getInetAddress().getHostName()
                                        + channel.socket().getPort()+" "+"query not found");
                            }
                            // TODO 查询项目信息
                        } else if (label[0].equals("query_Exam")) {
                            String itemId = label[1];
                            ExamItem examItem = toolFuns.getDataBase().getItems().get(itemId);
                            if (examItem!=null) {
                                msg = examItem.getItemId() + ";" + examItem.getExamName()
                                        + ";" + examItem.getInId() + ";" + examItem.getRestrId()
                                        + ";" + examItem.getExamTime() + ";" + examItem.getPreConstr();
                                System.out.println(msgInfo+channel.socket().getInetAddress().getHostName()
                                        + channel.socket().getPort()+" "+"query found");
                            } else {
                                msg = "not found";
                                System.out.println(msgInfo+channel.socket().getInetAddress().getHostName()
                                        + channel.socket().getPort()+" "+"query not found");
                            }
                            // TODO 加入新患者
                        } else if (label[0].equals("add_newPatient")) {
                            Patient patient = null;
                            String paId = label[1];
                            String name = label[2];
                            String sex = label[3];
                            int age = Integer.parseInt(label[4]);
                            String pacChoose = label[5];
                            int arrTime = Integer.parseInt(label[6]);
                            String limit = label[7];
                            patient = new Patient(paId, name, sex, age, pacChoose, arrTime, limit);
                            if (pacChoose.equals("a")) {
                                patient.setAllExams(toolFuns.getDataBase().getPackageA().getItemId());
                                System.out.println(msgInfo+channel.socket().getInetAddress().getHostName()
                                        + channel.socket().getPort()+" "+"add succeed");
                            }
                            else if (pacChoose.equals("b")) {
                                patient.setAllExams(toolFuns.getDataBase().getPackageB().getItemId());
                                System.out.println(msgInfo+channel.socket().getInetAddress().getHostName()
                                        + channel.socket().getPort()+" "+"add succeed");
                            }
                            else if (pacChoose.equals("c")) {
                                patient.setAllExams(toolFuns.getDataBase().getPackageC().getItemId());
                                System.out.println(msgInfo+channel.socket().getInetAddress().getHostName()
                                        + channel.socket().getPort()+" "+"add succeed");
                            }
                            else if (pacChoose.equals("d")) {
                                patient.setAllExams(toolFuns.getDataBase().getPackageD().getItemId());
                                System.out.println(msgInfo+channel.socket().getInetAddress().getHostName()
                                        + channel.socket().getPort()+" "+"add succeed");
                            }else{
                                System.out.println(msgInfo+channel.socket().getInetAddress().getHostName()
                                        + channel.socket().getPort()+" "+"add not succeed");
                                continue;
                            }
                            toolFuns.getDataBase().getPatients().put(paId,patient);
                        }else if(label[0].equals("queryTrends")){//queryTrends 10001
                            // TODO 增加查询此患者所选套餐所有仪器的排队状况的功能
                            if(toolFuns.getDataBase().getPatients().get(label[1])==null){
                                msg = "not found";
                                System.out.println(msgInfo+channel.socket().getInetAddress().getHostName()
                                        + channel.socket().getPort()+" "+"query not found");
                            }else{
                                ArrayList<Instrument> instruments=new ArrayList<>();
                                HashSet<String> canChoose = new HashSet<>(toolFuns.getDataBase().getPatients().get(label[1]).getCanChoose());
                                for(String eId:canChoose){
                                    Instrument i=new Instrument(toolFuns.getDataBase().getItems().get(eId).getInId(),
                                            toolFuns.getDataBase().getInstruments().get(toolFuns.getDataBase().getItems().get(eId).getInId()).getPatientQueue(),
                                            toolFuns.getDataBase().getInstruments().get(toolFuns.getDataBase().getItems().get(eId).getInId()).getInsName());
                                    instruments.add(i);
                                }
                                HashMap<String,Integer> costs=new HashMap<>();
                                for (Instrument ins:instruments){
                                    costs.put(ins.getInsId(),0);
                                }
                                for (String itemId:toolFuns.getDataBase().getItems().keySet()){
                                    ExamItem item=toolFuns.getDataBase().getItems().get(itemId);
                                    if (costs.containsKey(item.getInId())){
                                        costs.put(item.getInId(),item.getExamTime());
                                    }
                                }
                                String re="";
                                for(Instrument instrument:instruments){
                                    re+=instrument.getInsName()+"-"+Integer.toString(instrument.getPatientQueue().size())
                                            +"-" +Integer.toString(instrument.getPatientQueue().size()*costs.get(instrument.getInsId()))
                                            +";";
                                }
                                Patient patient = toolFuns.getDataBase().getPatients().get(label[1]);
                                re+=toolFuns.recommend2(patient);
//                                System.out.println(re);
                                msg=re;
                            }
                        }else if(label[0].equals("queryAll")){
                            String pac=label[1];
                            String re=pac;
                            switch (pac){
                                case "a":
                                    for (String itemId:toolFuns.getDataBase().getPackageA().getItemId()){
                                        ExamItem item=toolFuns.getDataBase().getItems().get(itemId);
                                        Instrument ins=toolFuns.getDataBase().getInstruments().get(item.getInId());
                                        double time=ins.getPatientQueue().size()*item.getExamTime();
                                        re+=";"+ins.getInsName()+"-"+time;
                                    }
                                    break;
                                case "b":
                                    for (String itemId:toolFuns.getDataBase().getPackageB().getItemId()){
                                        ExamItem item=toolFuns.getDataBase().getItems().get(itemId);
                                        Instrument ins=toolFuns.getDataBase().getInstruments().get(item.getInId());
                                        double time=ins.getPatientQueue().size()*item.getExamTime();
                                        re+=";"+ins.getInsName()+"-"+time;
                                    }
                                    break;
                                case "c":
                                    for (String itemId:toolFuns.getDataBase().getPackageC().getItemId()){
                                        ExamItem item=toolFuns.getDataBase().getItems().get(itemId);
                                        Instrument ins=toolFuns.getDataBase().getInstruments().get(item.getInId());
                                        double time=ins.getPatientQueue().size()*item.getExamTime();
                                        re+=";"+ins.getInsName()+"-"+time;
                                    }
                                    break;
                                case "d":
                                    for (String itemId:toolFuns.getDataBase().getPackageD().getItemId()){
                                        ExamItem item=toolFuns.getDataBase().getItems().get(itemId);
                                        Instrument ins=toolFuns.getDataBase().getInstruments().get(item.getInId());
                                        double time=ins.getPatientQueue().size()*item.getExamTime();
                                        re+=";"+ins.getInsName()+"-"+time;
                                    }
                                    break;
                            }
                            msg=re;
                        }
                        //-----------------------------------------

                        if (msg_1.equals("interruptConnection")) {//若收到结束，则清空列表
                            key.cancel();
//                            printPatientInfo();
                            System.out.println(msgInfo+channel.socket().getInetAddress().getHostName()
                                    + channel.socket().getPort()+" "+"interrupted connection");
                            running=false;
                            break;
                        }

                        //-----------------返回结果-----------------
                        CharsetEncoder encoder = Charset.forName("UTF-8").newEncoder();
                        channel.write(encoder.encode(CharBuffer.wrap(msg)));
//                        System.out.println(1);
                        //-----------------------------------------

                        channel.register(selector, SelectionKey.OP_READ);
                    }
                }
            }
        } catch (ClosedChannelException e) {
            // TODO Auto-generated catch block
            e.printStackTrace();
//            System.out.println(info+"客户端中断");
        } catch (CharacterCodingException e) {
            // TODO Auto-generated catch block
            e.printStackTrace();
        } catch (SocketException e){
            System.out.println("###log:"+"client unexpected interrupt");
        } catch (IOException e) {
            // TODO Auto-generated catch block
            e.printStackTrace();
        } finally {
            //关闭
            try {
//                printPatientInfo();
//                System.out.println("/********End********/");
                System.out.println("###log:"+"STOP!");
                running=false;
                selector.close();
                server.close();
            } catch (IOException e) {
                // TODO Auto-generated catch block
                e.printStackTrace();
            }
        }
    }

    public void setRunning(boolean f) {
        this.running = f;
    }

    public int getAddress() {
        return address;
    }

    public void setAddress(int address) {
        this.address = address;
    }

    public int getTimeOut() {
        return timeOut;
    }

    public void setTimeOut(int timeOut) {
        this.timeOut = timeOut;
    }

    public int getNumPatient() {
        return numPatient;
    }

    public void setNumPatient(int numPatient) {
        this.numPatient = numPatient;
    }

    public void printPatientInfo() {
        System.out.println("/---------------------------------------------------/");
        System.out.println(toolFuns.getTIME() + "min:");
        for(String pId:toolFuns.getDataBase().getPatients().keySet()){
            Patient patient=toolFuns.getDataBase().getPatients().get(pId);
            System.out.println("患者id：" + patient.getPaId());
            System.out.println("项目id\t" + "仪器id\t" + "到达时间\t" + "开始时间\t" + "所需时间\t" + "结束时间\t");
            for (Form form : patient.getForms()) {
                System.out.println(form.getExamId() + "\t    " + form.getInsId() + "\t    " + form.getArrTime() + "\t    " + form.getStartTime() + "\t    " + form.getTakeTime() + "\t    " + form.getEndTime());
            }
        }
        System.out.println("/---------------------------------------------------/");
    }

    public  void printPatientInfo2(){
        System.out.println("/---------------------------------------------------/");
        System.out.println(toolFuns.getTIME() + "min:");
        for(String pId:toolFuns.getDataBase().getPatients().keySet()){
            Patient patient=toolFuns.getDataBase().getPatients().get(pId);
            if(patient.getStatus()==-1){
                continue;
            }
            System.out.println("患者id：" + patient.getPaId());
            System.out.println("项目id\t" + "仪器id\t" + "到达时间\t" + "开始时间\t" + "所需时间\t" + "结束时间\t");
            for (Form form : patient.getForms()) {
                System.out.println(form.getExamId() + "\t    " + form.getInsId() + "\t    " + form.getArrTime() + "\t    " + form.getStartTime() + "\t    " + form.getTakeTime() + "\t    " + form.getEndTime());
            }
        }
        System.out.println("/---------------------------------------------------/");
    }

    public ToolFunctions getToolFuns() {
        return this.toolFuns;
    }

    public boolean getRun(){
        return running;
    }
}
