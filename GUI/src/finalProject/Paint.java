package finalProject;

import java.awt.*;
import java.awt.event.*;
import java.awt.geom.AffineTransform;
import java.awt.geom.Ellipse2D;
import java.awt.geom.Line2D;
import java.awt.image.BufferedImage;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Scanner;
import java.util.concurrent.TimeUnit;

import javax.imageio.ImageIO;
import javax.swing.*;


public class Paint extends JPanel implements ActionListener {
	/**
	 * 
	 */
	private static final long serialVersionUID = 1L;

	Timer t = new Timer(50, this);
	
	int x = 460;
	int y = 460;
	int diameter = 60;
	int radius = 30;
	
	
	double scanAngle = 0;
	

	
	int width;
	int distance;
	int angle;
	int textLines = 0;
	int currAngle = 0;
	
	boolean newObject;
	boolean scanning;
	
	ArrayList<Integer> distances = new ArrayList<Integer>();
	ArrayList<Integer> widths = new ArrayList<Integer>();
	ArrayList<Integer> angles = new ArrayList<Integer>();
	
	ArrayList<Integer> yObjects = new ArrayList<Integer>();
	ArrayList<Integer> xObjects = new ArrayList<Integer>();
	
	ArrayList<Integer> yDrops = new ArrayList<Integer>();
	ArrayList<Integer> xDrops = new ArrayList<Integer>();
	ArrayList<Integer> dropAngles = new ArrayList<Integer>();
	ArrayList<Integer> dropSideAngle = new ArrayList<Integer>();
	
	
	ArrayList<Integer> yTape = new ArrayList<Integer>();
	ArrayList<Integer> xTape = new ArrayList<Integer>();
	ArrayList<Integer> tapeAngles = new ArrayList<Integer>();
	ArrayList<Integer> tapeSideAngle = new ArrayList<Integer>();
	
	
	ArrayList<Integer> yBumps = new ArrayList<Integer>();
	ArrayList<Integer> xBumps = new ArrayList<Integer>();
	ArrayList<Integer> bumpAngles = new ArrayList<Integer>();
	
	double velX = 0;
	double velY = 0;
	double speed = 1;

	
	private BufferedImage image;


	
	
	
	public Paint() {
		
		t.start();
		setFocusable(true);
		setFocusTraversalKeysEnabled(false);
	
		
	}
	
	
	
	
	public void paintComponent(Graphics g) {
		super.paintComponent(g);
		
		
		Color pitFallColor = new Color(111,16,16);
		g.setColor(pitFallColor);
		
		
		

		//******************************************************************************************************
		for(int i = 0; i < xObjects.size(); i++) {						//loops through objects and repaints them
			g.drawOval(xObjects.get(i)-widths.get(i)/2, yObjects.get(i)-widths.get(i)/2, widths.get(i), widths.get(i));
		}
		//******************************************************************************************************
		
		
		
		
		//******************************************************************************************************
		for(int i = 0; i < xDrops.size(); i++) {						//loops through drops and repaints them
			Line2D line = new Line2D.Double(xDrops.get(i) -30, yDrops.get(i) - 20, xDrops.get(i) - 30, yDrops.get(i) + 20);
			AffineTransform at = AffineTransform.getRotateInstance(Math.toRadians(dropAngles.get(i)+dropSideAngle.get(i)), xDrops.get(i), yDrops.get(i));
			((Graphics2D) g).draw(at.createTransformedShape(line));
			

		}
		//******************************************************************************************************
		
		
		
		
		//******************************************************************************************************
		for(int i = 0; i < xTape.size(); i++) {						//loops through tape boundries and repaints them
			Line2D line = new Line2D.Double(xTape.get(i) -30, yTape.get(i) - 20, xTape.get(i) - 30, yTape.get(i) + 20);
			AffineTransform at = AffineTransform.getRotateInstance(Math.toRadians(tapeAngles.get(i)+tapeSideAngle.get(i)), xTape.get(i), yTape.get(i));
			((Graphics2D) g).draw(at.createTransformedShape(line));
			

		}
		//******************************************************************************************************
		
		
		
		
		//******************************************************************************************************
		for(int i = 0; i < xBumps.size(); i++) {							
			int xPos = Math.round((float) (x+Math.cos(currAngle + 45) *  radius));
			int yPos = Math.round((float) (y+Math.cos(currAngle + 45) *  radius));
				

																						//loops through bumps and keeps repaints them
			g.drawOval(xPos, yPos, 35, 35);
		}
		//******************************************************************************************************
		
		
		
		
		
		
		//******************************************************************************************************
		if(scanning == true) {										//performs the sweep
			Line2D line = new Line2D.Double(x , y, x+50, y+50);
			AffineTransform at = AffineTransform.getRotateInstance(Math.toRadians(scanAngle+currAngle-90  -45), x, y);
			((Graphics2D) g).draw(at.createTransformedShape(line));
		}
		//******************************************************************************************************

		
		
		
		
		//******************************************************************************************************
		Graphics2D g2 = (Graphics2D)g;								//draws the oval and pointer for which direction we are facing
		
		Line2D line = new Line2D.Double(x , y, x+50, y+50);
		AffineTransform at = AffineTransform.getRotateInstance(Math.toRadians(currAngle - 45), x, y);
		((Graphics2D) g).draw(at.createTransformedShape(line));
		
		Line2D line2 = new Line2D.Double(x , y, x+50, y+50);
		AffineTransform at2 = AffineTransform.getRotateInstance(Math.toRadians(currAngle - 45 - 90), x, y);
		((Graphics2D) g).draw(at2.createTransformedShape(line2));
		
		Line2D line3 = new Line2D.Double(x , y, x+50, y+50);
		AffineTransform at3 = AffineTransform.getRotateInstance(Math.toRadians(currAngle - 45 + 90), x, y);
		((Graphics2D) g).draw(at3.createTransformedShape(line3));
		
		g.drawOval(x-30, y-30, 60, 60);
		//******************************************************************************************************



		newObject = true;
	}

	
	
	@Override
	public void actionPerformed(ActionEvent arg0) {		
		
		if(x < 0 || x > 940) {
			velX = 0;
			x = 0;
		}
		
		if(y < 0 || y > 940) {
			velY = 0;
			y = 0;
		}
		

		
		
		x += velX;
		y += velY;
		
		//FileScan here
		
		
		
		//******************************************************************************************************
		if(scanning == true) {
			scanAngle += 2;
			if(scanAngle >= 180) {				//increments scanAngle if it is scanning
				scanning = false;
			}
		}
		//******************************************************************************************************
		
		
		
		
		repaint();
			
		//System.out.println("X: " + x + "     Y: " + y  + "     Distances: " + distances + "     Widths: " + widths + "     Angles: " 
		//+ angles +  "   " + textLines + "    CurrentAngle: " + currAngle + "    " + scanning + " " + scanAngle + "   bumpsX: "+ xBumps + "   bumpsY: " + yBumps);
	
	}
	
	
	
	
	public void up() {
		velY = -speed;
		velX = 0;
	}
	
	public void down() {
		velY = speed;
		velX = 0;
	}
	
	public void left() {
		velX = -speed;
		velY = 0;
		
	}
	
	public void right() {
		velX = speed;
		velY = 0;
	}
	
	
	public void fileScan(String toRead) {
		//File file = new File ("data.txt");
		Scanner sc = new Scanner(toRead);
	
		while(sc.hasNext()) {

		    String command = sc.next();
		    
		    
		    
		    
			//******************************************************************************************************
		    if(command.equalsIgnoreCase("Object")) {
		    	
		    	width = sc.nextInt();
		    	distance = sc.nextInt() + 60;
		    	angle = sc.nextInt();

				widths.add(width);
				distances.add(distance);						//case for if the bot detects a tall object/pillar
				angles.add(angle);
				
				int relativeAngle = (currAngle - 90) + (angles.get(angles.size() - 1));
				
				int objY = (int) ((Math.sin(Math.toRadians(relativeAngle))) * distance + y);
			    int objX = (int) ((Math.cos(Math.toRadians(relativeAngle))) * distance  + x);
			    
			    yObjects.add(objY);
			    xObjects.add(objX);

		    }
			//******************************************************************************************************
		    
		    
		    
		    
			//******************************************************************************************************
		    if(command.equalsIgnoreCase("Bump")){
		    	
		    	String side = sc.next();
		    	
		    	int bumpWidth  = 35;
		    	int bumpDistance = 0;
		    	bumpAngles.add(currAngle);
		    	int bumpAngle = currAngle = 45;
		    	
				int objY = (int) ((Math.sin(Math.toRadians(currAngle))) * distance + y);
			    int objX = (int) ((Math.cos(Math.toRadians(currAngle))) * distance  + x);
		    	
		    	
		    	xBumps.add(objX);
		    	yBumps.add(objY);
		    	
		    }
			//******************************************************************************************************
		    
		    
		    
		    
		    
			//******************************************************************************************************
		    if(command.equalsIgnoreCase("Drop")) {
		    	String side = sc.next();
		    	
		    	if(side.equalsIgnoreCase("Left")) {
		    		dropSideAngle.add(+90);
		    	}
		    	
		    	else if(side.equalsIgnoreCase("Right")) {
		    		dropSideAngle.add(-90);
		    	}
		    	
		    	else if(side.equalsIgnoreCase("LeftCenter")) {
		    		dropSideAngle.add(-45 + 180);								//case for detecting a drop
		    	}
		    	
		    	else if(side.equalsIgnoreCase("RightCenter")) {
		    		dropSideAngle.add(45 + 180);
		    	}
		    	
		    	else if(side.equalsIgnoreCase("Center")) {
		    		dropSideAngle.add(180);
		    	}
		    	
		    	dropAngles.add(currAngle);
		    	
		    	yDrops.add(y);
		    	xDrops.add(x);
		    	
		    }
			//******************************************************************************************************
		    
		    
		    
		    
		    
			//******************************************************************************************************
		    if(command.equalsIgnoreCase("Tape")) {
		    	String side = sc.next();
		    	
		    	if(side.equalsIgnoreCase("Left")) {
		    		tapeSideAngle.add(+90);
		    	}
		    	
		    	else if(side.equalsIgnoreCase("Right")) {
		    		tapeSideAngle.add(-90);
		    	}
		    	
		    	else if(side.equalsIgnoreCase("LeftCenter")) {
		    		tapeSideAngle.add(-45 + 180);						//case for hitting tape boundry
		    	}
		    	
		    	else if(side.equalsIgnoreCase("RightCenter")) {
		    		tapeSideAngle.add(45 + 180);
		    	}
		    	
		    	else if(side.equalsIgnoreCase("Center")) {
		    		tapeSideAngle.add(180);
		    	}
		    	
		    	tapeAngles.add(currAngle);
		    	
		    	yTape.add(y);
		    	xTape.add(x);
		    	
		    }
			//******************************************************************************************************
		    

		    
		    
		    
		    
			//******************************************************************************************************
		    if(command.equalsIgnoreCase("Sweep")){								//Makes scanning true if sweep is passed through
		    	scanning = true;
		    }
			//******************************************************************************************************
		    
		    
		    
		    
		    
		    
			//******************************************************************************************************
		    if(command.equalsIgnoreCase("Angle")){
		    	int newAngle= sc.nextInt();
		    	int tempAngle;
		    tempAngle = (int) (newAngle*2.821 + currAngle);
		    	
		    	if(tempAngle >= 360) {
		    		currAngle = tempAngle - 360;
		    	}
		    	
		    	else if(tempAngle < 0) {							//Case for angle, adds angle to currAngle and wraps back around if it gets to 360
		    		currAngle = tempAngle + 360;
		    	}
		    	
		    	else {
		    		currAngle = tempAngle;
		    	}
		    	
		    }
			//******************************************************************************************************
		    
		    
		    
		    
		    
		    
			//******************************************************************************************************
		    if(command.equalsIgnoreCase("Move")) {
		    	int distanceMoved = sc.nextInt();
		    	
		    	if(currAngle == 0) {
		    		x += distanceMoved*4;
		    	}
		    	
		    	else if(currAngle == 90) {
		    		y += distanceMoved*4;
		    	}
		    	
		    	else if(currAngle == 180) {							//for the case move, moves in the direction of the angle the bot is facing and the given distance
		    		x -= distanceMoved*4;
		    	}
		    	
		    	else if(currAngle == 270) {
		    		y -= distanceMoved*4;
		    	}
		    	
		    	else {
		    		
				y = (int) (Math.sin(currAngle*0.01745) * distanceMoved*4 + y);
				x = (int) (Math.cos(currAngle*0.01745) * distanceMoved*4 + x);
		    	
		    	}
		    	
		    }
			//******************************************************************************************************
		    
		    
		    

		    
			if(sc.hasNextLine()) {
				sc.nextLine();
			}
			
			textLines++;
		}
		
		

		sc.close();
	}
	
	

	
	
	

	

}
