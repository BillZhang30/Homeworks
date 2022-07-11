package src;

import javax.swing.*;
import javax.swing.border.EmptyBorder;
import javax.swing.table.DefaultTableModel;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.FocusEvent;
import java.awt.event.FocusListener;
import java.util.Vector;
/**
 * @author 19190217 lys
 * @version 0.1.1.20220311
 */
public class MedicalGuidanceLogin extends JFrame {

	private static final long serialVersionUID = -3831811672815174133L;

	//* 初始化控件 *//

	//容器
	Box verticalBoxSearchAndTable;
	Box horizontalBoxVboxAndCard;

	JPanel jPanelSearch;
	JScrollPane jScrollPaneTable;
	JTextField jTextSearch;//患者ID输入框
	JButton jButtonSearch;
	JTable jTable;// 表格
	DefaultTableModel defaultTableModel;// 表格模式
	public Vector<String> columnName = new Vector<>();
	public Vector<Vector<String>> rowsVector = new Vector<>();// 患者信息表格



	//展示面板
	public CardLayout cardLayoutPacks=new CardLayout(5,5);
	JPanel jPanelPacksCard;//实现1:进度条信息面板
	Box BoxProgressBars;//实现2:进度条盒子面板

	JPanel jPanelPackA;
	JProgressBar jProgressBarA1;
	JProgressBar jProgressBarA2;
	JProgressBar jProgressBarA3;
	JProgressBar jProgressBarA4;
	JProgressBar jProgressBarA5;
	JProgressBar jProgressBarA6;
	JProgressBar jProgressBarA7;
	JProgressBar jProgressBarA8;
	JProgressBar jProgressBarA9;
	JProgressBar jProgressBarA10;
	JProgressBar jProgressBarA11;
	JProgressBar jProgressBarA12;
	JProgressBar jProgressBarA13;



	// 命令字符串
	String command = "none";
	// 储存服务器查询的套餐
	String packageID;
	//储存
	int queueTimeMAX;
	int itemsNumber;

	//初始化定时器和监听器

	private final Timer timer;   //定时器
	private static final  int DELAY = 5000;  //定时器的间隔

	//由定时器 timer控制的监听器,每隔一段时间发送查询信息
	private class ReboundListener implements ActionListener {
		@Override
		public void actionPerformed(ActionEvent actionEvent) {
			packageID = jTextSearch.getText();
			if (packageID.equals("")) {
				Object[] options = {"OK ", "CANCEL "};
				JOptionPane.showOptionDialog(null, "您还没有输入 ", "提示", JOptionPane.DEFAULT_OPTION,
						JOptionPane.WARNING_MESSAGE, null, options, options[0]);
			} else {
				command = "queryTrends" + ";" + packageID;
			}
//			defaultTableModel.setRowCount(0);
		}
	}



	/**
	 * @apiNote 界面初始化函数功能 初始化各个组件
	 */
	public MedicalGuidanceLogin() {
		super("分诊导医智能调度子系统");//JFrame的构造方法

		//初始化面板
		initJPanelSearch();
		initJScrollPaneTable();
		initJPanelPackA();
//		initPanelProgressBars();

		//初始化容器
		verticalBoxSearchAndTable =Box.createVerticalBox();
		verticalBoxSearchAndTable.setBorder(BorderFactory.createTitledBorder("查询"));
		verticalBoxSearchAndTable.add(jPanelSearch);
		verticalBoxSearchAndTable.add(jScrollPaneTable);

		horizontalBoxVboxAndCard=Box.createHorizontalBox();
		horizontalBoxVboxAndCard.add(verticalBoxSearchAndTable);
		horizontalBoxVboxAndCard.add(jPanelPackA);

		//初始化JFrame
		Dimension screenSize =Toolkit.getDefaultToolkit().getScreenSize();
		System.out.println("Screen Size: "+screenSize.width+"*"+screenSize.height);
		this.setSize(screenSize.width, screenSize.height); // 设置大小
//		this.setLocation(0,0);
		this.setLocationRelativeTo(null);// 将窗体位于屏幕的中央
//		this.setExtendedState(MAXIMIZED_BOTH);
		this.setVisible(true);
		this.setDefaultCloseOperation(EXIT_ON_CLOSE);
		this.setResizable(true);
		this.add(horizontalBoxVboxAndCard);
		this.pack();

		//初始化计时器
		timer = new Timer(DELAY,new ReboundListener());
		// 窗口关闭按钮的事件监听与处理: 点击关闭按钮，向服务器发送中断连接的命令
		this.addWindowListener(new java.awt.event.WindowAdapter() {
			public void windowClosing(java.awt.event.WindowEvent windowEvent) {command = "interruptConnection";}
		});
	}

	private void initJPanelSearch(){
		//初始化并设置组件
		jTextSearch =new JTextField("请输入套餐",30);
		jTextSearch.setEditable(true);
		jTextSearch.setFont(new Font(null,Font.PLAIN,18));
		jTextSearch.setSelectionColor(Color.gray);
		jTextSearch.setSelectedTextColor(Color.WHITE);
		//搜索文本框的事件监听与处理: 用鼠标焦点监听器来提示用户输入
		jTextSearch.addFocusListener(new FocusListener() {
			// 得到焦点时，当前文本框的提示文字和创建该对象时的提示文字一样，说明用户正要键入内容
			public void focusGained(FocusEvent e) {
				if (jTextSearch.getText().equals("请输入套餐")) {
					jTextSearch.setText(""); // 将提示文字清空
					jTextSearch.setForeground(Color.black); // 设置用户输入的字体颜色为黑色
				}
			}
			// 失去焦点时，用户尚未在文本框内输入任何内容，所以依旧显示提示文字
			public void focusLost(FocusEvent e) {
				if (jTextSearch.getText().equals("")) {
					jTextSearch.setForeground(Color.gray); // 将提示文字设置为灰色
					jTextSearch.setText("请输入套餐"); // 显示提示文字
				}
			}
		});
		Font fontButton = new Font("思源黑体", Font.PLAIN,18);
		jButtonSearch = new JButton();
		jButtonSearch.setText("    查询    ");
		jButtonSearch.setFont(fontButton);
		//查询按钮的事件监听与处理: 用户输入ID后,点击查询按钮,向服务器发送查询消息
		jButtonSearch.addActionListener(actionEvent -> {
			//获取文本框里输入的内容
			packageID = jTextSearch.getText();
			//如果输入框里没有输入
			if (packageID.equals("")) {
				Object[] options = { "OK ", "CANCEL " };
				JOptionPane.showOptionDialog(null, "您还没有输入 ", "提示", JOptionPane.DEFAULT_OPTION,
						JOptionPane.WARNING_MESSAGE, null, options, options[0]);
			}
			//如果输入框里输入了内容,则生成命令字符串准备发送给服务器
			else {
				command = "queryAll" + ";" + packageID;
			}
//			//点击查询后就启动定时器,定时刷新查询
			timer.start();
//			defaultTableModel.setRowCount(0);
		});
		//如果构造时输入文本,setFont会抛出nullpointer异常.

		//创建面板容器并添加组件
		FlowLayout flowLayoutSearch =new FlowLayout(FlowLayout.CENTER);
		jPanelSearch = new JPanel(flowLayoutSearch);
		jPanelSearch.setBorder(new EmptyBorder(10,0,10,0));
		jPanelSearch.add(jTextSearch);
		jPanelSearch.add(jButtonSearch);
	}

	private void initJScrollPaneTable() {
		//表格
		columnName = new Vector<>();
		columnName.add("检查项目名称");
		columnName.add("预计排队时间");
		defaultTableModel = new DefaultTableModel(rowsVector, columnName);
		jTable = new JTable(defaultTableModel);
		jScrollPaneTable = new JScrollPane(jTable,
				ScrollPaneConstants.VERTICAL_SCROLLBAR_ALWAYS,
				ScrollPaneConstants.HORIZONTAL_SCROLLBAR_ALWAYS);
		//响应鼠标滚动
		jScrollPaneTable.setWheelScrollingEnabled(true);
		jScrollPaneTable.setBorder(BorderFactory.createTitledBorder("您当前的检查项目如下:"));
	}

	//实现方式之一:动态布局方式

//	private void initPanelProgressBars(){
////		jPanelPackProgressBar =new JPanel();
////		jPanelPackProgressBar.setBorder(BorderFactory.createTitledBorder("当前排队人数一览") );
//		BoxProgressBars=Box.createVerticalBox();
//		BoxProgressBars.setBorder(BorderFactory.createTitledBorder("当前排队人数一览") );
//	}


//	public void initPackProgressBars(){
////		jPanelPackProgressBar.setLayout(new GridLayout(itemsNumber,1,5,5));
//		//套餐最少为9个
//		for(int i=0;i<9;i++){
//			jProgressBarVector.add(new JProgressBar(0,queueTimeMAX));
//			jProgressBarVector.get(i).setString(rowAttributes.get(i).get(0));
//			jProgressBarVector.get(i).setValue(Integer.parseInt(rowAttributes.get(i).get(1)));
//			jProgressBarVector.get(i).setBackground(new Color(
//					255*(1-(jProgressBarVector.get(i).getValue()/queueTimeMAX)),
//					255*(jProgressBarVector.get(i).getValue()/queueTimeMAX),
//					0));
//			jProgressBarVector.get(i).setOrientation(SwingConstants.HORIZONTAL);
//			jProgressBarVector.get(i).setBorderPainted(true);
//			jProgressBarVector.get(i).setStringPainted(true);
//			BoxProgressBars.add(jProgressBarVector.get(i));
////			jPanelPackProgressBar.add(jProgressBarVector.get(i));
//		}
//	}
//
//	public void addProgressBars(int itemsNumber){
//		for(int i=9;i<itemsNumber;i++){
//			jProgressBarVector.add(new JProgressBar(0,queueTimeMAX));
//			jProgressBarVector.get(i).setString(rowAttributes.get(i).get(0));
//			jProgressBarVector.get(i).setValue(Integer.parseInt(rowAttributes.get(i).get(1)));
//			jProgressBarVector.get(i).setBackground(new Color(
//					255*(1-(jProgressBarVector.get(i).getValue()/queueTimeMAX)),
//					255*(jProgressBarVector.get(i).getValue()/queueTimeMAX),
//					0));
//			jProgressBarVector.get(i).setOrientation(SwingConstants.HORIZONTAL);
//			jProgressBarVector.get(i).setBorderPainted(true);
//			jProgressBarVector.get(i).setStringPainted(true);
//			BoxProgressBars.add(jProgressBarVector.get(i));
//		}
//	}

	private void initJPanelPackA(){
		jPanelPackA =new JPanel(new GridLayout(13,1,5,5));
		jProgressBarA1=new JProgressBar(0,10);
		jProgressBarA2=new JProgressBar(0,10);
		jProgressBarA3=new JProgressBar(0,10);
		jProgressBarA4=new JProgressBar(0,10);
		jProgressBarA5=new JProgressBar(0,10);
		jProgressBarA6=new JProgressBar(0,10);
		jProgressBarA7=new JProgressBar(0,10);
		jProgressBarA8=new JProgressBar(0,10);
		jProgressBarA9=new JProgressBar(0,10);
		jProgressBarA10=new JProgressBar(0,10);
		jProgressBarA11=new JProgressBar(0,10);
		jProgressBarA12=new JProgressBar(0,10);
		jProgressBarA13=new JProgressBar(0,10);
	}

	public void getPanelPackA(){
		jProgressBarA1.setString(rowsVector.get(0).get(0));
		jProgressBarA2.setString(rowsVector.get(1).get(0));
		jProgressBarA3.setString(rowsVector.get(2).get(0));
		jProgressBarA4.setString(rowsVector.get(3).get(0));
		jProgressBarA5.setString(rowsVector.get(4).get(0));
		jProgressBarA6.setString(rowsVector.get(5).get(0));
		jProgressBarA7.setString(rowsVector.get(6).get(0));
		jProgressBarA8.setString(rowsVector.get(7).get(0));
		jProgressBarA9.setString(rowsVector.get(8).get(0));
		jProgressBarA10.setString(rowsVector.get(9).get(0));
		jProgressBarA11.setString(rowsVector.get(10).get(0));
		jProgressBarA12.setString(rowsVector.get(11).get(0));
		jProgressBarA13.setString(rowsVector.get(12).get(0));
		jProgressBarA1.setValue((int)Double.parseDouble(rowsVector.get(0).get(1)));
		jProgressBarA2.setValue((int)Double.parseDouble(rowsVector.get(1).get(1)));
		jProgressBarA3.setValue((int)Double.parseDouble(rowsVector.get(2).get(1)));
		jProgressBarA4.setValue((int)Double.parseDouble(rowsVector.get(3).get(1)));
		jProgressBarA5.setValue((int)Double.parseDouble(rowsVector.get(4).get(1)));
		jProgressBarA6.setValue((int)Double.parseDouble(rowsVector.get(5).get(1)));
		jProgressBarA7.setValue((int)Double.parseDouble(rowsVector.get(6).get(1)));
		jProgressBarA8.setValue((int)Double.parseDouble(rowsVector.get(7).get(1)));
		jProgressBarA9.setValue((int)Double.parseDouble(rowsVector.get(8).get(1)));
		jProgressBarA10.setValue((int)Double.parseDouble(rowsVector.get(9).get(1)));
		jProgressBarA11.setValue((int)Double.parseDouble(rowsVector.get(10).get(1)));
		jProgressBarA12.setValue((int)Double.parseDouble(rowsVector.get(11).get(1)));
		jProgressBarA13.setValue((int)Double.parseDouble(rowsVector.get(12).get(1)));
		jPanelPackA.add(jProgressBarA1);
		jPanelPackA.add(jProgressBarA2);
		jPanelPackA.add(jProgressBarA3);
		jPanelPackA.add(jProgressBarA4);
		jPanelPackA.add(jProgressBarA5);
		jPanelPackA.add(jProgressBarA6);
		jPanelPackA.add(jProgressBarA7);
		jPanelPackA.add(jProgressBarA8);
		jPanelPackA.add(jProgressBarA9);
		jPanelPackA.add(jProgressBarA10);
		jPanelPackA.add(jProgressBarA11);
		jPanelPackA.add(jProgressBarA12);
		jPanelPackA.add(jProgressBarA13);
	}

/*	private void drawArc(Graphics g) {
		Graphics2D g2d = (Graphics2D) g.create();
		//抗锯齿
		//JDK文档：http://tool.oschina.net/uploads/apidocs/jdk-zh/java/awt/RenderingHints.html
		g2d.setRenderingHint(RenderingHints.KEY_ANTIALIASING, RenderingHints.VALUE_ANTIALIAS_ON);
		int width = getWidth();
		int height = getHeight();
		//设置画笔颜色
		g2d.setColor(Color.BLACK);
		g2d.drawArc(width / 2 - 110, height / 2 - 110, 10 + 200, 10 + 200, 0, 360);
		g2d.setColor(Color.RED);
		g2d.fillArc(width / 2 - 110, height / 2 - 110, 10 + 200, 10 + 200, STEP, 240);
		g2d.setColor(Color.BLACK);
		g2d.fillArc(width / 2 - 90, height / 2 - 90, 10 + 160, 10 + 160, 0, 360);
		g2d.dispose();
	}*/

	//命令设定与获取
	public void setCommand(String command) {
		this.command = command;
	}

	public String getCommand() {
		return command;
	}

}