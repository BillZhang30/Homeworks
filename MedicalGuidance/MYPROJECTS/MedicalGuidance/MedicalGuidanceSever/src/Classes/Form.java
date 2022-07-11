package Classes;

import java.util.Objects;

public class Form {
    private String examId;//项目id
    private String insId;//仪器id
//    private int currType;//当前状态
    private int arrTime;//到达时间
    private int startTime;//开始时间
    private int takeTime;//此检查所需时间
    private int endTime;//结束时间

    public Form(String examId, String insId, int arrTime, int startTime, int takeTime, int endTime) {
        this.examId = examId;
        this.insId = insId;
//        this.currType = currType;
        this.arrTime = arrTime;
        this.startTime = startTime;
        this.takeTime = takeTime;
        this.endTime = endTime;
    }

    public Form(int currType,int arrTime){
        this.arrTime=arrTime;
//        this.currType=currType;
    }

    public  Form(String eId){
        this.examId=eId;
    }

    public String getExamId() {
        return examId;
    }

    public void setExamId(String examId) {
        this.examId = examId;
    }

    public String getInsId() {
        return insId;
    }

    public void setInsId(String insId) {
        this.insId = insId;
    }

//    public int getCurrType() {
//        return currType;
//    }
//
//    public void setCurrType(int currType) {
//        this.currType = currType;
//    }

    public int getArrTime() {
        return arrTime;
    }

    public void setArrTime(int arrTime) {
        this.arrTime = arrTime;
    }

    public int getStartTime() {
        return startTime;
    }

    public void setStartTime(int startTime) {
        this.startTime = startTime;
    }

    public int getTakeTime() {
        return takeTime;
    }

    public void setTakeTime(int takeTime) {
        this.takeTime = takeTime;
    }

    public int getEndTime() {
        return endTime;
    }

    public void setEndTime(int endTime) {
        this.endTime = endTime;
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        Form form = (Form) o;
        return Objects.equals(examId, form.examId);
    }

    @Override
    public int hashCode() {
        return Objects.hash(examId);
    }
}
