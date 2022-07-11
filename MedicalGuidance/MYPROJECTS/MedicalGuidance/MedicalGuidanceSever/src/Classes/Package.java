package Classes;

import java.util.ArrayList;

public class Package {
    private ArrayList<String> itemId=new ArrayList<>();//套餐包含项目id列表

    public Package(ArrayList<String> itemId) {
        this.itemId = itemId;
    }

    public Package(){}

    public ArrayList<String> getItemId() {
        return itemId;
    }

    public void setItemId(ArrayList<String> itemId) {
        this.itemId = itemId;
    }
}
