// Mohamed Ali Ramadan (7688825)
// SEG 2106 - Assignment 4: Part A

public class OpenOfficeTest // Console Unit Test
{
	public static void main(String[] args) 
	{
		// Declare an office with two clean desks and one dirty desk.
		OpenOffice off = new OpenOffice(2,1);
		
		// Office has 2 Cleaners, IDs = 1,2.
		Cleaner c1 = new Cleaner(off, 1);
		c1.start();
		Cleaner c2 = new Cleaner(off, 2);
		c2.start();
		
		// Office has 4 Clerks, IDs = 1,2,3,4.
		Clerk k1 = new Clerk(off, 1);
		k1.start();
		Clerk k2 = new Clerk(off, 2);
		k2.start();
		Clerk k3 = new Clerk(off, 3);
		k3.start();
		Clerk k4 = new Clerk(off, 4);
		k4.start();
		
		try
		{
			c1.join();
			c2.join();
			k1.join();
			k2.join();
			k3.join();
			k4.join();
		}
		catch (Exception e) { }
	}
}
