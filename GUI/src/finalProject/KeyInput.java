package finalProject;

import java.awt.event.KeyAdapter;
import java.awt.event.KeyEvent;
import java.awt.event.KeyListener;

public class KeyInput extends KeyAdapter {
	
	private Putty putty;
	
	public KeyInput(Putty p) {
		
		putty = p;
		
	}
	
	public void keyPressed(KeyEvent e) {
	
		int key = e.getKeyCode();
		char c = e.getKeyChar();
		if (key == KeyEvent.VK_UP) {
			
			putty.writeToOutput("W");

			
		}
		else if (key == KeyEvent.VK_LEFT) {
			
			putty.writeToOutput("A");

		}
		else if (key == KeyEvent.VK_DOWN) {
			
			putty.writeToOutput("S");

			
		}
		else if (key == KeyEvent.VK_RIGHT) {
			
			putty.writeToOutput("D");

		}
		else if (c == 'a') {
			
			putty.writeToOutput("1");
			
		}
		else if (c == 's') {
			
			putty.writeToOutput("2");
			
		}
		else if (key == KeyEvent.VK_SPACE) {
			
			
			putty.writeToOutput("T");
		}
		
	}
	
	public void keyReleased(KeyEvent e) {
		System.out.println("B");
		putty.writeToOutput("B");
		
	}
	
}
