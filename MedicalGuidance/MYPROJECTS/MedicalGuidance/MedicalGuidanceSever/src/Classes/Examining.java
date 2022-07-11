package Classes;

public class Examining {
    private String examId;
    private String insId;
    private int startTime;
    private int arrTime;
    private int finTime;

    public Examining(String examId, int startTime) {
        this.examId = examId;
        this.startTime = startTime;
    }

    public Examining(){
        this.examId="";
        this.insId="";
        this.startTime=-1;
        this.arrTime=-1;
        this.finTime=-1;
    }

    public void reSet(){
        this.arrTime=finTime;
        this.examId="";
        this.insId="";
        this.startTime=-1;
        this.finTime=-1;
    }

    public String getExamId() {
        return examId;
    }

    public void setExamId(String examId) {
        this.examId = examId;
    }

    public int getStartTime() {
        return startTime;
    }

    public void setStartTime(int startTime) {
        this.startTime = startTime;
    }

    public int getArrTime() {
        return arrTime;
    }

    public void setArrTime(int arrTime) {
        this.arrTime = arrTime;
    }

    public int getFinTime() {
        return finTime;
    }

    public void setFinTime(int finTime) {
        this.finTime = finTime;
    }

    public String getInsId() {
        return insId;
    }

    public void setInsId(String insId) {
        this.insId = insId;
    }
}
