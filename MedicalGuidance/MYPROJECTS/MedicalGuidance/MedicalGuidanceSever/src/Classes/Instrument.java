package Classes;

import java.util.LinkedList;
import java.util.Objects;
import java.util.Queue;

public class Instrument {
    private String insId;//仪器id
    private String insName;//仪器名称
    private String position;//仪器位置
    /**获取系统时间，若今日处于维护时间段，则仪器设为不可用？*/
    private int fixPeriod;//仪器维护时间段
    private boolean canUse;
    private Queue<String> patientQueue=new LinkedList<>();

    public Instrument(String insId, String insName, String position, int fixPeriod) {
        this.insId = insId;
        this.insName = insName;
        this.position = position;
        this.fixPeriod = fixPeriod;
    }

    public  Instrument(String insId){
        this.insId=insId;
    }

    public Instrument(String insId,Queue<String> patientQueue,String insName){
        this.insId=insId;
        this.setPatientQueue(patientQueue);
        this.insName=insName;
    }

    public String getInsId() {
        return insId;
    }

    public void setInsId(String insId) {
        this.insId = insId;
    }

    public String getPosition() {
        return position;
    }

    public void setPosition(String position) {
        this.position = position;
    }

    public int getFixPeriod() {
        return fixPeriod;
    }

    public void setFixPeriod(int fixPeriod) {
        this.fixPeriod = fixPeriod;
    }

    public String getInsName() {
        return insName;
    }

    public void setInsName(String insName) {
        this.insName = insName;
    }

    public Queue<String> getPatientQueue() {
        return patientQueue;
    }

    public void setPatientQueue(Queue<String> patientQueue) {
        this.patientQueue = patientQueue;
    }

    public boolean isCanUse() {
        return canUse;
    }

    public void setCanUse(boolean canUse) {
        this.canUse = canUse;
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        Instrument that = (Instrument) o;
        return Objects.equals(insId, that.insId);
    }

    @Override
    public int hashCode() {
        return Objects.hash(insId);
    }
}
