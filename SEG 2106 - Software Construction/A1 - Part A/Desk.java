// Mohamed Ali Ramadan (7688825)
// SEG 2106 - Assignment 4: Part A

// Represents a common resource.
// Note this assignment does not require tracking 
// desk objects. So they will be only passed as objects to show 
// this possibility, but changes applied by the threads will
// be lost.
public class Desk 
{
	private boolean is_clean;
	
	public Desk()
	{
		this.is_clean = true;
	}
	
	public boolean isClean()
	{
		return this.is_clean;
	}
	
	public void makeDirty()
	{
		this.is_clean = false;
	}
	
	public void clean()
	{
		this.is_clean = true;
	}
}
