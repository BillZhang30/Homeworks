package src;

import javax.swing.*;
import java.io.IOException;
import java.net.UnknownHostException;
import java.util.*;

public class Main {
	public int itemNumber;
	int queueTimeSize;

	public static void main(String[] args) throws UnknownHostException, IOException, InterruptedException {
		NIOClientThread nIOCT = new NIOClientThread("localhost", 8081);
		nIOCT.start();
		System.out.println("Client start");
		MedicalGuidanceLogin mGLI = new MedicalGuidanceLogin();
//		mGLI.packageID="a";
//		mGLI.itemsNumber=11;
//		mGLI.queueTimeMAX=22;
		System.out.println("initializing Interface");

		//对界面发送的指令做解析
		while (mGLI.getCommand() != null) {
			//如果结果为none
			if (nIOCT.getAns().equals("none")) {
				Thread.sleep(800);
			}
			/*
			 * SEND：queryAll-d
			 * RETURN：
			 * a/b/c;insname-queuetime;insname-queuetime;........insname-queuetime;
			 *
			 */
			// 向服务器发送指令
			// 指令内容不是none的情况下,向服务器请求查询
			if (!mGLI.getCommand().equals("none")) {
				String[] label = mGLI.getCommand().split(";");
				if(label[0].equals("interruptConnection")) {
					nIOCT.setMsg(mGLI.getCommand());
					nIOCT.setWriting(true);
					mGLI.setCommand(null);
					break;
				}
				else if(label[0].equals("queryAll")){
					nIOCT.setMsg(mGLI.getCommand());
					nIOCT.setWriting(true);
					mGLI.setCommand("none");
					//break;!!!!!!!!!!!!!!!!!!
				}
			}
			//对服务器返回的查找结果做处理
			if (!nIOCT.getAns().equals("none")) {
				String ans = nIOCT.getAns();
				if (ans.equals("not found")) {
					JOptionPane.showMessageDialog(null, "查找失败");
					nIOCT.setAns("none");
				}
				else {
					//分割返回消息
					String[] insname_queuetimeStrings = ans.split(";");//分割为一个一个的insname-queuetime,第一个为package
					Vector<String> insname_queuetimeVector = new Vector<>(Arrays.asList(insname_queuetimeStrings));
					//提取位于返回结果最前面的套餐代号
					mGLI.packageID= insname_queuetimeVector.get(0);

					mGLI.itemsNumber=0;
					mGLI.queueTimeMAX=0;
					insname_queuetimeVector.remove(0);
					for(String item: insname_queuetimeVector){
						//分割开insName-queueTime
						String[] insname_queuetimeString =item.split("-");
						System.out.println(Arrays.toString(insname_queuetimeString));
						//获取最长的排队等待时间

						mGLI.queueTimeMAX=
								Math.max((int)Double.parseDouble(insname_queuetimeString[1]), mGLI.queueTimeMAX);
						//转换为Vector,填入表格
						Vector<String> tableRow = new Vector<>(Arrays.asList(insname_queuetimeString));
						mGLI.rowsVector.add(tableRow);//加入表格
						mGLI.itemsNumber++;
					}
					System.out.println("Items:"+ mGLI.itemsNumber+"\n QueueTimeMax:"+ mGLI.queueTimeMAX+
							"\n Package:"+ mGLI.packageID);
//					mGLI.defaultTableModel.setRowCount(0);
					mGLI.defaultTableModel.setDataVector(mGLI.rowsVector, mGLI.columnName);
					if(mGLI.rowsVector.size()>0){
						mGLI.getPanelPackA();
					}
					nIOCT.setAns("none");
				}//else
			}//if
		}//while
	}//main
}

//		20220405
//		四个问题
//		abcd表格只能显示一会
//		cd不显示进度条
//		进度条标准改成预计排队时间，合理安排长度区别
//		类型转换


//	20220420
//	数组越界