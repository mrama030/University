// Mohamed Ali Ramadan (7688825)
// SEG 2106 - Assignment 4: Part A

public class Cleaner extends Thread
{
	private Office office;
	private int ID;
	
	public Cleaner(Office off, int id)
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
			System.out.println("CLEANER " + this.ID + " is LOOKING for a dirty desk.");
			
			Desk desk = office.service();
			System.out.println("CLEANER " + this.ID + " has FOUND a dirty desk.");
			
			// Cleaning Time
			try 
			{
				sleep(1500);
			} 
			catch (InterruptedException e) { }

			office.cleaned(desk);
			System.out.println("CLEANER " + this.ID + " is DONE cleaning the desk.");
		}
	}
}
