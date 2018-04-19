package finalProject;

import java.io.BufferedInputStream;
import java.io.BufferedReader;
import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStream;
import java.io.OutputStreamWriter;
import java.io.PrintWriter;
import java.io.StringWriter;
import java.net.InetAddress;
import java.net.Socket;
import java.net.UnknownHostException;
import java.util.Scanner;

public class Putty {

	private Socket socket = null;
	private DataInputStream input = null;
	private OutputStream output = null;
	private OutputStreamWriter out = null;
	private BufferedReader reader = null;
	private Paint p;
	public Putty(Paint paint) {
		
		
		
		try {
			
			 socket = new Socket("192.168.1.1",288);
			 output = socket.getOutputStream();
			 input = new DataInputStream(new BufferedInputStream(socket.getInputStream()));
			 reader = new BufferedReader(new InputStreamReader(input));
			 out = new OutputStreamWriter(output, "UTF-8");
			 p = paint;
			 

		}catch (UnknownHostException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		/*
		String line = "";
		
		while (!line.equals("Over")) {
			
			try {
				
			line = input.readUTF();
			//output.writeUTF(line);
			}
			catch (IOException i) {
				
				System.out.println(i);
			}
			
		}
		*/
		
		
	}
	public void readInput() {
		
		String line;
		
		try {
			if (reader.ready()) {
			//if ((line = input.readUTF()) != null) {	
				line = reader.readLine();
				p.fileScan(line);
				System.out.println(line);
				
			}
			
				 
		} 
		catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		
	}
	
	public void writeToOutput(String next) {
		
		//System.out.println(next);
		try {
			
			if (next != null && next.length() == 1) {
				
				out.write((int) next.charAt(0));
				out.flush();
				//readInput();
			}
			
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		
	}
	
}
