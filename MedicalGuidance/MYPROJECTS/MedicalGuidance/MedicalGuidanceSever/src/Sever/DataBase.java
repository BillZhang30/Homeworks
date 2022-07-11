package Sever;

import Classes.*;

import java.sql.*;
import java.util.ArrayList;
import java.util.HashMap;


//

public class DataBase {//数据库操作类
    int arrTime = 0;//患者到达时间 单位为分钟
    Connection conn = null;//创建数据库连接对象
    private HashMap<String,Patient> patients= new HashMap<>();//所有的患者
    private HashMap<String,Instrument> instruments= new HashMap<>();//所有的仪器
    private HashMap<String,ExamItem> items= new HashMap<>();//所有的项目
    private PackageA packageA;//A套餐列表
    private PackageB packageB;//B套餐列表
    private PackageC packageC;//C套餐列表
    private PackageD packageD;//D套餐列表

//    private String number;

    public DataBase(String number) throws SQLException {
        //读数据库***要初始化可选列表，实时去掉或更新****要根据某些仪器限制，让患者跳过此检查/不可选此套餐
        //可选队列与未完成队列之间的关系？可选队列作为可选的所有项目列表，与受限之前的包含的所有项目做对比
        getConnection();
        String sql = "select  * from patient limit "+number+";";//****一次读入多少数据

        readInstrument();
        readExamItem();
        readPackageA();
        readPackageB();
        readPackageC();
        readPackageD();
        readPatient(sql);
    }

    private void getConnection() throws SQLException {//连接数据库
        final String JDBC_DRV = "com.mysql.cj.jdbc.Driver";
        final String URL = "jdbc:mysql://localhost:3306/hospital_queue?characterEncoding=utf8&useSSL=true&rewriteBatchedStatements=true";
        final String USER = "root";
        final String password = "Z39676014";
        try {
            Class.forName(JDBC_DRV);  //注册数据库驱动
            conn = DriverManager.getConnection(URL,USER,password); //获取数据连接
//            System.out.println("数据库连接成功");
        } catch (ClassNotFoundException | SQLException e) {
            // TODO Auto-generated catch block
            e.printStackTrace();
        }
    }

    private void readInstrument() throws SQLException { //读取所有仪器信息
        String sql = "select * from instrumentinfo;";
        PreparedStatement preparedStatement = null;
        ResultSet resultSet = null;
        preparedStatement = conn.prepareStatement(sql);
//        System.out.println("执行sql：" + sql);
        resultSet = preparedStatement.executeQuery(sql);
        while (resultSet.next()) {
            String iID = resultSet.getString("IID");//仪器ID
            String instrumentName = resultSet.getString("InstrumentName");//仪器名称
            String position = resultSet.getString("Position");//仪器所在科室
            String periodOfFix = resultSet.getString("Period-of-Fix");//仪器检修时间段

            Instrument _ins = new Instrument(iID, instrumentName, position, Integer.parseInt(periodOfFix));
            instruments.put(iID,_ins);
//            System.out.println("仪器ID：" + _ins.getInsId() + " 仪器名称：" + _ins.getInsName() +
//                    " 所在科室：" + _ins.getPosition() + " 检修时段：" + _ins.getFixPeriod());
        }
    }

    private void readExamItem() throws SQLException { //读取所有检查项目信息
        String sql = "select * from examitem;";
        PreparedStatement preparedStatement = null;
        ResultSet resultSet = null;
        preparedStatement = conn.prepareStatement(sql);
//        System.out.println("执行sql：" + sql);
        resultSet = preparedStatement.executeQuery(sql);
        while (resultSet.next()) {
            String itemID = resultSet.getString("ItemID");//项目ID
            String examName = resultSet.getString("ExamName");//项目名称
            String preConstraint = resultSet.getString("Pre-Constraint");//项目前置约束
            if (preConstraint == null || preConstraint.isEmpty()) {
                preConstraint = "NULL";
            }
            String restriction = resultSet.getString("Restriction");//项目限制条件
            if (restriction == null || restriction.isEmpty()) {
                restriction = "NULL";
            }
            String instrumentID = resultSet.getString("InstrumentID");//项目所需仪器ID
            int time = resultSet.getInt("Time");//项目所需时间

            ExamItem _exam = new ExamItem(itemID, time, examName, preConstraint, restriction, instrumentID);
            items.put(itemID,_exam);
//            System.out.println("项目ID：" + _exam.getItemId() + " 项目名称：" + _exam.getExamName() +
//                    " 项目前置约束：" + _exam.getPreConstr() + " 项目限制条件：" + _exam.getRestrId()
//                    + " 项目所需仪器ID：" + _exam.getInId() + " 项目所需时间：" + _exam.getExamTime());
        }
    }

    private void readPackageA() throws SQLException { //读取套餐A
        String sql = "select * from package_a;";
        PreparedStatement preparedStatement = null;
        ArrayList<String> packageAList = new ArrayList<>();//暂存数据库读取的内容
        ResultSet resultSet = null;
        preparedStatement = conn.prepareStatement(sql);
//        System.out.println("执行sql：" + sql);
        resultSet = preparedStatement.executeQuery(sql);
//        System.out.println("PackageA所含项目(ID): ");
        while (resultSet.next()) {
            String _item = resultSet.getString("Item");//项目ID
            packageAList.add(_item);
//            System.out.println(_item + " ");
        }

        packageA=new PackageA(packageAList);
    }

    private void readPackageB() throws SQLException { //读取套餐B
        String sql = "select * from package_b;";
        PreparedStatement preparedStatement = null;
        ArrayList<String> PackageBList = new ArrayList<>();//暂存数据库读取的内容
        ResultSet resultSet = null;
        preparedStatement = conn.prepareStatement(sql);
//        System.out.println("执行sql：" + sql);
        resultSet = preparedStatement.executeQuery(sql);
//        System.out.println("PackageB所含项目(ID): ");
        while (resultSet.next()) {
            String _item = resultSet.getString("Item");//项目ID
            PackageBList.add(_item);
//            System.out.println(_item + " ");
        }
        packageB=new PackageB(PackageBList);
    }

    private void readPackageC() throws SQLException { //读取套餐C
        String sql = "select * from package_c;";
        PreparedStatement preparedStatement = null;
        ArrayList<String> PackageCList = new ArrayList<>();//暂存数据库读取的内容
        ResultSet resultSet = null;
        preparedStatement = conn.prepareStatement(sql);
//        System.out.println("执行sql：" + sql);
        resultSet = preparedStatement.executeQuery(sql);
//        System.out.println("PackageC所含项目(ID): ");
        while (resultSet.next()) {
            String _item = resultSet.getString("Item");//项目ID
            PackageCList.add(_item);
//            System.out.println(_item + " ");
        }

        packageC = new PackageC(PackageCList);
    }

    private void readPackageD() throws SQLException { //读取套餐D
        String sql = "select * from package_d;";
        PreparedStatement preparedStatement = null;
        ArrayList<String> PackageDList = new ArrayList<>();//暂存数据库读取的内容
        ResultSet resultSet = null;
        preparedStatement = conn.prepareStatement(sql);
//        System.out.println("执行sql：" + sql);
        resultSet = preparedStatement.executeQuery(sql);
//        System.out.println("PackageD所含项目(ID): ");
        while (resultSet.next()) {
            String _item = resultSet.getString("Item");//项目ID
            PackageDList.add(_item);
//            System.out.println(_item + " ");
        }

        packageD = new PackageD(PackageDList);
    }

    private void readPatient(String sql) throws SQLException { //读取患者信息
        PreparedStatement preparedStatement = null;
        ResultSet resultSet = null;
        preparedStatement = conn.prepareStatement(sql);
//        System.out.println("执行sql：" + sql);
        resultSet = preparedStatement.executeQuery(sql);
        while (resultSet.next()) {
            String pid = resultSet.getString("PID");
            String name = resultSet.getString("Name");
            String sex = resultSet.getString("Sex");
            int age = resultSet.getInt("Age");
            String package_ = resultSet.getString("Package");
            String constraint = resultSet.getString("Restriction");
            if (constraint == null || constraint.isEmpty()) {
                constraint = "NULL1";
            }
            Patient _pt = new Patient(pid, name, sex, age, package_, arrTime, constraint);

            if (package_.equals("a")) {
                for (String itemId : packageA.getItemId()) {
                    _pt.getAllExams().add(itemId);
                }
            }
            if (package_.equals("b")) {
                for (String itemId : packageB.getItemId()) {
                    _pt.getAllExams().add(itemId);
                }
            }
            if (package_.equals("c")) {
                for (String itemId : packageC.getItemId()) {
                    _pt.getAllExams().add(itemId);
                }
            }

            arrTime += 10;//设定每隔十分钟到达一位患者
            patients.put(pid,_pt);
//            System.out.println("姓名：" + _pt.getPaId() + " 性别：" + _pt.getSex() +
//                    " 年龄：" + _pt.getAge() + " 套餐：" + _pt.getPacChoose() + " 时间:" + _pt.getArrTime());
        }

        try {
            if(resultSet!=null)
            {
                resultSet.close();//关闭结果集
            }
            if(preparedStatement!=null)
            {
                preparedStatement.close();//关闭preparedstatement
            }
            if(conn!=null)
            {
                conn.close();//关闭数据库连接
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    public HashMap<String,Patient> getPatients() {
        return patients;
    }

    public void setPatients(HashMap<String,Patient> patients) {
        this.patients = patients;
    }

    public HashMap<String,Instrument> getInstruments() {
        return instruments;
    }

    public void setInstruments(HashMap<String,Instrument> instruments) {
        this.instruments = instruments;
    }

    public HashMap<String,ExamItem> getItems() {
        return items;
    }

    public void setItems(HashMap<String,ExamItem> items) {
        this.items = items;
    }

    public PackageA getPackageA() {
        return packageA;
    }

    public void setPackageA(PackageA packageA) {
        this.packageA = packageA;
    }

    public PackageB getPackageB() {
        return packageB;
    }

    public void setPackageB(PackageB packageB) {
        this.packageB = packageB;
    }

    public PackageC getPackageC() {
        return packageC;
    }

    public void setPackageC(PackageC packageC) {
        this.packageC = packageC;
    }

    public PackageD getPackageD() {
        return packageD;
    }

    public void setPackageD(PackageD packageD) {
        this.packageD = packageD;
    }
}
