package Classes;

import java.util.ArrayList;
import java.util.Objects;

public class Patient {
    private String paId;//患者id
    private String name;//患者名字
    private String sex;//患者性别
    private int age;//患者年龄
    private String pacChoose;//患者选择的套餐
    private int arrTime;//到达时间
    private Examining examining=new Examining();//当前检查仪器相关
    private String limit;
    private int status=-1;//当前状态 -1为未进入 0为待推荐；1为正在检查；2为在排队；3为结束

    private  ArrayList<String> allExams=new ArrayList<>();//套餐所有项目*
    private ArrayList<String> canChoose;//可选项目列表*
    private ArrayList<String> open;//未完成项目*
    private ArrayList<String> close=new ArrayList<>();//已完成项目

    private ArrayList<Form> forms=new ArrayList<>();//患者状态更新表格

    public Patient(String paId, String name, String sex, int age, String pacChoose, int arrTime, String limit) {
        this.paId = paId;
        this.name = name;
        this.sex = sex;
        this.age = age;
        this.pacChoose = pacChoose;
        this.arrTime = arrTime;
        this.limit = limit;
        this.status=-1;
    }

    public Patient(String paId){
        this.paId=paId;
    }

    public String getPaId() {
        return paId;
    }

    public void setPaId(String paId) {
        this.paId = paId;
    }

    public String getSex() {
        return sex;
    }

    public void setSex(String sex) {
        this.sex = sex;
    }

    public int getAge() {
        return age;
    }

    public void setAge(int age) {
        this.age = age;
    }

    public String getPacChoose() {
        return this.pacChoose;
    }

    public void setPacChoose(String pacChoose) {
        this.pacChoose = pacChoose;
    }

    public ArrayList<Form> getForms() {
        return forms;
    }

    public void setForms(ArrayList<Form> forms) {
        this.forms = forms;
    }

    public int getArrTime() {
        return arrTime;
    }

    public void setArrTime(int arrTime) {
        this.arrTime = arrTime;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public ArrayList<String> getCanChoose() {
        return canChoose;
    }

    public void setCanChoose(ArrayList<String> canChoose) {
        this.canChoose = new ArrayList<>(canChoose);
    }

    public ArrayList<String> getOpen() {
        return open;
    }

    public void setOpen(ArrayList<String> open) {
        this.open = new ArrayList<>(open);
    }

    public ArrayList<String> getClose() {
        return close;
    }

    public void setClose(ArrayList<String> close) {
        this.close = new ArrayList<>(close);
    }

    public boolean findPre(String eid){
        if(close.contains(eid)){
            return true;
        }
        else{
            return false;
        }
    }

    public ArrayList<String> getAllExams() {
        return allExams;
    }

    public void setAllExams(ArrayList<String> allExams) {
        this.allExams = new ArrayList<String>(allExams);
    }

    public int getStatus() {
        return status;
    }

    public void setStatus(int status) {
        this.status = status;
    }

    public Examining getExamining() {
        return examining;
    }

//    public void setExamining(Examining examining) {
//        this.examining = examining;
//    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        Patient patient = (Patient) o;
        return Objects.equals(paId, patient.paId) ;
    }

    @Override
    public int hashCode() {
        return Objects.hash(paId);
    }

    public String getLimit() {
        return limit;
    }

    public void setLimit(String limit) {
        this.limit = limit;
    }

    public void printAll(){
        System.out.println(paId+" "+allExams+" "+canChoose+" "+open+" "+close);
    }
}
