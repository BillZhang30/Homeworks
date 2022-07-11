import Classes.Form;
import Classes.Patient;
import Sever.Server;

import java.util.Scanner;

public class Main {
    //query patientInfo 10001
    public static void main(String[] args) throws InterruptedException {
        String localInfo="$local:";
        Server myServer;
        myServer = new Server(8081,5000,1000);
        myServer.start();
        Scanner scan=new Scanner(System.in);
        while(scan.hasNext()){
            String command= scan.nextLine();
            String[] label =command.split(" ");
            if(command.equals("quit")){//退出命令
                myServer.setRunning(false);
                System.out.println("want to quit mainThread?(y/n)");
                Scanner sc=new Scanner(System.in);
                if(sc.next().equals("y")){
                    System.out.println(localInfo+"退出");
                    break;
                }else {
                    System.out.println(localInfo + "quit sever only");
                    continue;
                }
            }else if(label[0].equals("query")){//查询患者信息
                if(label.length==3&&label[1].equals("patientInfo")){
                    Patient patient = myServer.getToolFuns().getDataBase().getPatients().get(label[2]);
                    if (patient == null) {
                        System.out.println(localInfo + "not found");
                        continue;
                    }
                    System.out.println("/-----------" + localInfo + "-----------/");
                    System.out.println(myServer.getToolFuns().getTIME() + "min:");
                    System.out.println("患者id：" + patient.getPaId());
                    System.out.println("项目id\t" + "仪器id\t" + "到达时间\t" + "开始时间\t" + "所需时间\t" + "结束时间\t");
                    for (Form form : patient.getForms()) {
                        System.out.println(form.getExamId() + "\t    " + form.getInsId() + "\t    " + form.getArrTime() + "\t    " + form.getStartTime() + "\t    " + form.getTakeTime() + "\t    " + form.getEndTime());
                    }
                    System.out.println("/-----------" + "patientInfo" + "-----------/");
                }
            }else if(command.equals("queryAll")){
                System.out.println("/-----------" + localInfo + "-----------/");
                myServer.printPatientInfo();
            }else if(command.equals("queryAll-no-Waiting")) {
                System.out.println("/-----------" + localInfo + "-----------/");
                myServer.printPatientInfo2();
            }else if(command.equals("rs")){
                if(myServer.getRun()==true){
                    System.out.println("###log:"+"stop first");
                    continue;
                }
                myServer.setRunning(true);
                myServer.run();
            }
            else{
                System.out.println(localInfo + "unuseful command");
            }
            System.out.flush();
        }
        myServer.interrupt();
    }
}
