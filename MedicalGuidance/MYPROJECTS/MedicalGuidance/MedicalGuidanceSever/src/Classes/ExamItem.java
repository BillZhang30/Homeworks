package Classes;

import java.util.Objects;

public class ExamItem {
    private String itemId;//项目id
    private int examTime;//项目所需时间
    private String examName;//项目名称
    private String preConstr;//前置项目id
    private String restrId;//限制id
    private String inId;//所需仪器id

    public ExamItem(String itemId, int examTime, String examName, String preExam, String restrId, String inId) {
        this.itemId = itemId;
        this.examTime = examTime;
        this.examName = examName;
        this.preConstr = preExam;
        this.restrId = restrId;
        this.inId = inId;
    }

    public ExamItem(){}

    public ExamItem(String itemId){
        this.itemId=itemId;
    }

    public String getItemId() {
        return itemId;
    }

    public void setItemId(String itemId) {
        this.itemId = itemId;
    }

    public String getPreConstr() {
        return preConstr;
    }

    public void setPreConstr(String preConstr) {
        this.preConstr = preConstr;
    }

    public String getRestrId() {
        return restrId;
    }

    public void setRestrId(String restrId) {
        this.restrId = restrId;
    }

    public String getInId() {
        return inId;
    }

    public void setInId(String inId) {
        this.inId = inId;
    }

    public String getExamName() {
        return examName;
    }

    public void setExamName(String examName) {
        this.examName = examName;
    }

    public int getExamTime() {
        return examTime;
    }

    public void setExamTime(int examTime) {
        this.examTime = examTime;
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        ExamItem examItem = (ExamItem) o;
        return Objects.equals(itemId, examItem.itemId);
    }

    @Override
    public int hashCode() {
        return Objects.hash(itemId);
    }

}