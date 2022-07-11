package src;

import java.io.IOException;
import java.net.InetSocketAddress;
import java.nio.ByteBuffer;
import java.nio.CharBuffer;
import java.nio.channels.ClosedChannelException;
import java.nio.channels.SelectionKey;
import java.nio.channels.Selector;
import java.nio.channels.SocketChannel;
import java.nio.charset.*;
import java.util.Iterator;

public class NIOClientThread extends Thread {
	private CharsetDecoder decoder = StandardCharsets.UTF_8.newDecoder();
	private CharsetEncoder encoder = StandardCharsets.UTF_8.newEncoder();
	private Selector selector = null;
	private SocketChannel socket = null;
	private SelectionKey clientKey = null;
	private boolean running;
	private String msg;
	private boolean writing;
	String ans = "none";

	public String getAns() {
		return ans;
	}

	/**
	 * @apiNote 连接服务器
	 */
	public NIOClientThread(String host, int port) {
		running = true;
		writing = false;

		try {
			// 创建一个Selector
			selector = Selector.open();

			// 创建并注册Socket
			socket = SocketChannel.open();
			socket.configureBlocking(false);
			clientKey = socket.register(selector, SelectionKey.OP_CONNECT);

			// 连接到远程地址
			InetSocketAddress ip = new InetSocketAddress(host, port);
			socket.connect(ip);
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}

	/**
	 * @apiNote 运行客户端
	 * @apiNote 读取服务器发送的信息
	 * @apiNote 向服务器发送信息
	 */
	public void run() {
		try {
			// 监听事件

			while (running) {
				selector.select(1);
				// 事件来源列表
				Iterator<SelectionKey> it = selector.selectedKeys().iterator();
				while (it.hasNext()) {
					SelectionKey key = it.next();
					// 删除当前事件
					it.remove();

					// 判断当前事件类型
					if (key.isConnectable()) {
						// 连接事件
						SocketChannel channel = (SocketChannel) key.channel();
						if (channel.isConnectionPending()) {
							channel.finishConnect();
						}
						channel.register(selector, SelectionKey.OP_WRITE);
//						System.out.println("连接服务器端成功！");
					}
					else if (key.isReadable()) {
						SocketChannel channel = (SocketChannel) key.channel();
						// 读取服务器发来的数据
						// --------------读取数据-----------
						ByteBuffer buffer = ByteBuffer.allocate(1024);
						channel.read(buffer);
						buffer.flip();
						// 读取到的信息
						ans = decoder.decode(buffer).toString();
//						System.out.println(ans);

						channel.register(selector, SelectionKey.OP_WRITE);
						break;
//						this.wait();

					}
					else if (key.isWritable() && writing) {
//						System.out.println("我在写，所以现在的信息是：" + msg);

						SocketChannel channel = (SocketChannel) key.channel();
						if (msg.equals("interruptConnection")) {
							channel.write(encoder.encode(CharBuffer.wrap(msg)));
							msg = null;
							writing = false;
							running = false;
							break;
						}
						// 发送
						if (msg != null) {// 写了才读，不写不读
//							System.out.println("我进入了写的条件判断!");
							channel.write(encoder.encode(CharBuffer.wrap(msg)));
							msg = null;
							writing = false;
							channel.register(selector, SelectionKey.OP_READ);
//							System.out.println("我写完成了！");
//							Thread.sleep(100);
						}
						else {
							channel.register(selector, SelectionKey.OP_WRITE);
						}
					}//if

				}//while
			}
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} finally {
			try {
				selector.close();
				socket.close();
			} catch (IOException e) {
				e.printStackTrace();
			}
		}
	}

	public String getMsg() {
		return msg;
	}

	public void setMsg(String msg) {
		this.msg = msg;
	}

	public void setAns(String ans) {
		this.ans = ans;
	}

	public boolean isRunning() {
		return running;
	}

	public void setRunning(boolean running) {
		this.running = running;
	}

	public boolean isWriting() {
		return writing;
	}

	public void setWriting(boolean writing) {
		this.writing = writing;
	}
}
