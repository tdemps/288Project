package finalProject;

import java.awt.Dimension;
import java.awt.event.KeyEvent;
import java.awt.event.KeyListener;
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.Scanner;

import javax.swing.JFrame;

public class Gui extends JFrame implements KeyListener {
	
	private Putty putty;
	private KeyInput keys;
	private Paint p;
	
	public Gui() {
		
		JFrame frame = new JFrame("FrameDemo");
		p = new Paint();
		p.addKeyListener(this);
		putty = new Putty(p);
		keys = new KeyInput(putty);
		frame.add(p);
		frame.addKeyListener(this);
		frame.setSize(1000,1000);
		frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		frame.setTitle("GUI");
		//frame.pack();
		frame.setVisible(true);

		/*
		//2. Optional: What happens when the frame closes?
		frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

		//3. Create components and put them in the frame.
		//...create emptyLabel...
		frame.setExtendedState(JFrame.MAXIMIZED_BOTH); 
		frame.setUndecorated(true);
		//4. Size the frame.
		frame.pack();
		//5. Show it.
		frame.setVisible(true);
		System.out.println(frame.getWidth());*/
		
	}
	
	public static void main(String[] args) {
		
		
		Gui g = new Gui();
		//this.addKeyListener(keys);
		BufferedReader s = new BufferedReader(new InputStreamReader(System.in));
		String whatsNext = "1";
		while (!whatsNext.equals("Exit")) {
			
			
				
			g.putty.readInput();
			try {
				if (s.ready()) {
					
					whatsNext = s.readLine();
					g.putty.writeToOutput(whatsNext);
				}
			} catch (IOException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
			
		
			
		}
		
		
		
	}
	
	@Override
	public void keyTyped(KeyEvent e) {
		keys.keyTyped(e);
	}

	@Override
	public void keyPressed(KeyEvent e) {
		// TODO Auto-generated method stub
		//System.out.println("hello");
		keys.keyPressed(e);
	}

	@Override
	public void keyReleased(KeyEvent e) {
		// TODO Auto-generated method stub
		keys.keyReleased(e);
	}
	
	
	
	
}