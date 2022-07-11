package Sever;

import Classes.ExamItem;
import Classes.Form;
import Classes.Instrument;
import Classes.Patient;

import java.sql.SQLException;
import java.text.SimpleDateFormat;
import java.util.ArrayList;
import java.util.Date;

public class ToolFunctions {
    private int TIME=0;//模拟时间流
    public int getTIME(){
        return this.TIME;
    }//获取当前时间
    public void addTIME(){
        TIME++;
    }//时间流
    private final DataBase data;//读取数据类实例化
    public DataBase getDataBase(){
        return data;
    }
//    private ArrayList<Patient> patient_in=new ArrayList<>();//将进入患者

    public ToolFunctions(String number) throws SQLException {
        data=new DataBase(number);/*可替换函数*/
    }

    /**
     * 函数名：isPreDone
     * 功能：判断当前项目的前置项目是否已完成或为空
     * 参数：当前患者，需要判断的项目id
     * 返回值：boolean
     */
    private boolean isPreDone(Patient p,String id){
        ExamItem examItem=data.getItems().get(id);//找到此id对应的项目
        if(examItem.getItemId().equals(id)){
//            System.out.println(examItem.getPreConstr());
            if(examItem.getPreConstr().equals("NULL")||examItem.getPreConstr().isBlank()||examItem.getPreConstr().isEmpty()||examItem.getPreConstr()==null){
                return true;//若无前置项目则返回
            }
            else{
                return p.findPre(examItem.getItemId());//此id对应的项目的前置项目id是否已经被检查过
            }
        }

        return true;
    }

    /**
     * 函数名：findFinishTime
     * 作用：通过患者的id以及项目的id，查到此患者检查此项目的结束时间,选择需要获取的时间（0为到达时间1为开始时间2为结束时间）
     * 参数：患者id，项目id
     * 返回值：开始检查的时间
     */
    private int findPatientExamTime(String pId,String examId,String insId,int m){
//        System.out.println(pId+" "+examId+" "+insId);
        //找到此id对应的项目

        Patient p=data.getPatients().get(pId);//找到此患者

        Form f=new Form(examId);
        int index=p.getForms().indexOf(f);//找到此患者的对应表内此项目的对应索引

        if(insId!=null){
            return switch (m) {
                case 0 -> p.getExamining().getArrTime();
                case 1 -> p.getExamining().getStartTime();
                case 2 -> p.getExamining().getFinTime();
                default -> 0;
            };
        }

        return switch (m) {
            case 0 -> p.getForms().get(index).getArrTime();
            case 1 -> p.getForms().get(index).getStartTime();
            case 2 -> p.getForms().get(index).getEndTime();
            default -> 0;
        };
    }

    /**
     * 函数名：calWaitingTime
     * 作用：通过项目id，计算当前正在检查此项目的患者的等待时间
     * 参数：项目id
     * 返回值：排队时间
     */
    private int calWaitingTime(ExamItem item){
        int waitingTime=0;

        Instrument ins=data.getInstruments().get(item.getInId());//找到此项目对应的仪器

        if (ins.getPatientQueue().peek()==null){//判断此项目所对应仪器是否有人在排队
            return waitingTime;
        }else{
            //由等待人数计算一部分等待时间
            waitingTime+=(ins.getPatientQueue().size()-1)*item.getExamTime();
            //由正在检查的人计算另一部分等待时间
            waitingTime+=findPatientExamTime(ins.getPatientQueue().peek(),item.getItemId(),ins.getInsId(),2)-TIME;
        }
        return waitingTime;
    }

    /**
     * 函数名：recommend
     * 功能：为当前患者推荐项目队列
     * 参数：患者
     * 返回值：无
     */
    private void recommend(Patient p){
        //计算可选队列中各仪器的响应比(改)，选择响应比最高的仪器
        double maxResponse=0;
        double cr;
        int waitTime;
        String bestInstId="";
        String bestExamId="";
        int checkTime=0;
        int bestWaitTime=0;
//        System.out.println(p.getOpen());
        for(String examId:p.getOpen()) {//未完成表中
            if (isPreDone(p, examId)) {//判断前置项目
                ExamItem ex = data.getItems().get(examId);//找到此id对应的项目

                waitTime = calWaitingTime(ex);
//                System.out.println(waitTime);
                if (waitTime == 0) {
                    cr = Integer.MAX_VALUE;
                } else {
                    cr = 1 + ex.getExamTime() / waitTime;//算出此候选项目的响应比
                }

                //求最大相应比
                if (cr > maxResponse) {
                    maxResponse = cr;
                    bestExamId = examId;
                    bestInstId = ex.getInId();
                    checkTime = ex.getExamTime();
                    bestWaitTime = waitTime;
                }
            }
        }

        if(checkTime==0){
            p.setStatus(3);
            p.getOpen().clear();
            return;
        }

        //加入新患者及其状态
        Form f=new Form(bestExamId,bestInstId,TIME,TIME+bestWaitTime,checkTime,TIME+bestWaitTime+checkTime);
        p.getForms().add(f);//更新此患者表格

//        System.out.println(p.getPaId()+" "+bestExamId);
        data.getInstruments().get(bestInstId).getPatientQueue().add(p.getPaId());//找到此项目对应的仪器并将此患者加入其排队队列

//        System.out.println(data.getInstruments().get(indexI).getPatientQueue().peek());

        p.setStatus(2);//状态设为在排队
        p.getExamining().setExamId(bestExamId);//设置患者当前项目
        p.getExamining().setInsId(bestInstId);//设置患者当前仪器
        p.getExamining().setArrTime(findPatientExamTime(p.getPaId(),bestExamId,null,0));//到达时间
        p.getExamining().setStartTime(findPatientExamTime(p.getPaId(),bestExamId,null,1));//患者当前项目的开始时间
        p.getExamining().setFinTime(findPatientExamTime(p.getPaId(), bestExamId,null,2));//结束时间
//        System.out.println(p.getExamining().getExamId());
    }

    /**
     * 函数名：refreshForm
     * 功能：更新所有患者状态
     * 参数：当前时间点
     * 返回值：无
     */
    public void refreshForm(){
        //更新所有患者状态

        for (String pId: data.getPatients().keySet()) {

            for(int j=0;j<5;j++){//每名患者在一时间点更新5次，保证正确性

//                System.out.println(data.getPatients().get(i).getPaId()+" "+data.getPatients().get(i).getStatus());

                if (data.getPatients().get(pId).getStatus() == 3) {//已结束则跳过
                    continue;
                }
                if(data.getPatients().get(pId).getStatus()==-1){//未进入的
                    if(data.getPatients().get(pId).getArrTime()==TIME){//到了进入的时间
//                    System.out.println(TIME+" "+data.getPatients().get(i).getArrTime());
                        recommend(data.getPatients().get(pId));
                    }
                }
                if (data.getPatients().get(pId).getStatus() == 0) {//待推荐的
                    if(data.getPatients().get(pId).getExamining().getArrTime()==TIME){//若到达下一个项目的到达时间
                        recommend(data.getPatients().get(pId));
                    }
                }
                if (data.getPatients().get(pId).getStatus() == 2) {//在排队的
                    if (data.getPatients().get(pId).getExamining().getStartTime() == TIME) {//若轮到他
                        data.getPatients().get(pId).setStatus(1);//设为在检查
                    }
                }
                if (data.getPatients().get(pId).getStatus() == 1) {//正在检查的
                    if (data.getPatients().get(pId).getExamining().getFinTime() == TIME) {//若已经结束

                        data.getPatients().get(pId).getOpen().remove(data.getPatients().get(pId).getExamining().getExamId());//删掉未完成项目

//                        data.getPatients().get(i).printAll();

                        data.getPatients().get(pId).getClose().add(data.getPatients().get(pId).getExamining().getExamId());//增加已完成项目

//                        data.getPatients().get(i).printAll();

                        data.getPatients().get(pId).getExamining().reSet();//清空当前仪器属性,并以之前结束项目时间为当前项目到达时间

                        if (data.getPatients().get(pId).getOpen().isEmpty()) {//如果未完成项目列表为空，则结束检查
                            data.getPatients().get(pId).setStatus(3);
                        }
                        else{
                            data.getPatients().get(pId).setStatus(0);
                        }
                    }
                }
            }
        }

    }

    /**
     * 函数名：getWeek
     * 功能：获得今日周几
     * 参数：date
     * 返回值：星期n
     */
    private String getWeek(Date date){
        SimpleDateFormat sdf = new SimpleDateFormat("EEEE");
        return sdf.format(date);
    }

    /**
     * 函数名：getFixTime
     * 功能：将当前时间更改为数据库维修时间格式
     * 参数：无
     * 返回值：1~10表示周一到周日上午或下午
     */
    private int getFixTime(){
        int re=0;
        Date date = new Date();
        String weekDay=getWeek(date);
        SimpleDateFormat df = new SimpleDateFormat("HH");
        String str = df.format(date);
        int a = Integer.parseInt(str);
        boolean amOrPm= a <= 12 || a > 24;
        switch (weekDay) {
            case "星期一":
                if (amOrPm) {
                    re = 1;
                } else {
                    re = 2;
                }
                break;
            case "星期二":
                if (amOrPm) {
                    re = 3;
                } else {
                    re = 4;
                }
                break;
            case "星期三":
                if (amOrPm) {
                    re = 5;
                } else {
                    re = 6;
                }
                break;
            case "星期四":
                if (amOrPm) {
                    re = 7;
                } else {
                    re = 8;
                }
                break;
            case "星期五":
                if (amOrPm) {
                    re = 9;
                } else {
                    re = 10;
                }
                break;
            case "星期六":
                if (amOrPm) {
                    re = 11;
                } else {
                    re = 12;
                }
                break;
            case "星期日":
                if (amOrPm) {
                    re = 13;
                } else {
                    re = 14;
                }
                break;
        }
        return re;
    }

    /**
     * 函数名：setInsFixPer
     * 功能：判断仪器是否在维修状态
     * 参数：无
     * 返回值：无
     */
    public void setInsFixPer(){
        for(String iId:data.getInstruments().keySet()){
            data.getInstruments().get(iId).setCanUse(data.getInstruments().get(iId).getFixPeriod() != getFixTime());
        }
    }

    /**
     * 函数名：setPatCan
     * 功能：设置患者可选仪器列表并初始化未检查仪器列表
     * 参数：无
     * 返回值：无
     */
    public void setPatCan() {
        //若此患者总项目表中有进入维修的仪器则将其从可选列表、未完成表中的相应项目删除
        //先获取所有项目，再根据限制或维修情况，去掉仪器对应的项目中的不可选项目，生成可选项目列表，再通过可选项目列表生成未完成项目列表

        for(String pId:data.getPatients().keySet()){//对于每一位患者
            if(data.getPatients().get(pId).getStatus()==-1){//若还没进入队列
                data.getPatients().get(pId).setCanChoose(data.getPatients().get(pId).getAllExams());//先初始化可选项目表
            }
        }

        setInsFixPer();//初始化仪器检修状态
        for(String pId:data.getPatients().keySet()){//对于每一位患者
            ArrayList<String> allExams = data.getPatients().get(pId).getAllExams();
            for (String eid : allExams) {//找到其所有项目列表
                String inId = data.getItems().get(eid).getInId();//找到此项目的对应仪器id

                if (!data.getInstruments().get(inId).isCanUse()) {//若仪器在检修
                    if (data.getPatients().get(pId).getStatus() == -1) {//若还没进入队列
                        data.getPatients().get(pId).getCanChoose().remove(eid);
                    } else {
                        data.getPatients().get(pId).getOpen().remove(eid);
                    }
                }
            }
        }

        for(String pId:data.getPatients().keySet()) {//对于每一位患者
            String str1 = data.getPatients().get(pId).getLimit();//获取其限制id
            ArrayList<String> allExams = data.getPatients().get(pId).getAllExams();
            for (String eid : allExams) {//找到其所有项目列表
                String str2 = data.getItems().get(eid).getRestrId();
                if (str1.equals(str2)) {
                    if (data.getPatients().get(pId).getStatus() == -1) {//若还没进入队列
                        data.getPatients().get(pId).getCanChoose().remove(eid);
                    } else {
                        data.getPatients().get(pId).getOpen().remove(eid);
                    }
                }
            }
        }

        for(String pId:data.getPatients().keySet()) {//对于每一位患者
            if(data.getPatients().get(pId).getStatus()==-1){
                data.getPatients().get(pId).setOpen(data.getPatients().get(pId).getCanChoose());//初始化可选列表
            }
        }
    }

    /**
     * 函数名：recommend1
     * 功能：只为患者推荐下一检查项目，但不改变状态
     * 参数：无
     * 返回值：无
     */
    public String recommend1(Patient p){
        //计算可选队列中各仪器的响应比(改)，选择响应比最高的仪器
        double maxResponse=0;
        double cr;
        int waitTime;
        String bestExamIdName="";
        int checkTime=0;
//        System.out.println(p.getOpen());
        for(String examId:p.getOpen()) {//未完成表中
            if (isPreDone(p, examId)) {//判断前置项目
                ExamItem ex = data.getItems().get(examId);//找到此id对应的项目

                waitTime = calWaitingTime(ex);
//                System.out.println(waitTime);
                if (waitTime == 0) {
                    cr = Integer.MAX_VALUE;
                } else {
                    cr = 1 + ex.getExamTime() / waitTime;//算出此候选项目的响应比
                }

                //求最大相应比
                if (cr > maxResponse) {
                    maxResponse = cr;
                    bestExamIdName=ex.getExamName();
                    checkTime = ex.getExamTime();
                }
            }
        }

        if(checkTime==0){
            return "无可推荐项目";
        }

        return bestExamIdName;
    }

    public String recommend2(Patient p){
        //计算可选队列中各仪器的响应比(改)，选择响应比最高的仪器
        double maxResponse=0;
        double cr;
        int waitTime;
        String bestExamId="";
        int checkTime=0;
//        System.out.println(p.getOpen());
        for(String examId:p.getOpen()) {//未完成表中
            if (isPreDone(p, examId)) {//判断前置项目
                ExamItem ex = data.getItems().get(examId);//找到此id对应的项目

                waitTime = calWaitingTime(ex);
//                System.out.println(waitTime);
                if (waitTime == 0) {
                    cr = Integer.MAX_VALUE;
                } else {
                    cr = 1 + ex.getExamTime() / waitTime;//算出此候选项目的响应比
                }

                //求最大相应比
                if (cr > maxResponse) {
                    maxResponse = cr;
                    bestExamId=ex.getItemId();
                    checkTime = ex.getExamTime();
                }
            }
        }

        if(checkTime==0){
            return "无可推荐项目";
        }

        ExamItem examItem=data.getItems().get(bestExamId);
        return data.getInstruments().get(examItem.getInId()).getInsName();
    }
}