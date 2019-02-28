// Mohamed Ali Ramadan (7688825)
// SEG 2106 - Assignment 4: Part A

public class Clerk extends Thread
{
	private Office office;
	private int ID;
	
	public Clerk(Office off, int id)
	{
		this.office = off;
		this.ID = id;
	}
	
	public Office getOffice()
	{
		return this.office;
	}
	
	public int getID()
	{
		return this.ID;
	}
	
	public void run()
	{
		while (true)
		{
			System.out.println("CLERK " + this.ID + " is LOOKING for a clean desk.");
			
			Desk desk = office.arrive();
			System.out.println("CLERK " + this.ID + " has ARRIVED at a clean desk.");
			
			// Working Time
			try 
			{
				sleep(2000);
			} 
			catch (InterruptedException e) { }
			
			office.leave(desk);
			System.out.println("CLERK " + this.ID + " has LEFT DESK.");
		}
	}
}
