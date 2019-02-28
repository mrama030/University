import java.util.concurrent.locks.Condition;
import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;

// Mohamed Ali Ramadan (7688825)
// SEG 2106 - Assignment 4: Part A

// Implementation of a monitor for an Office with many desks and two types of workers.
public class OpenOffice implements Office 
{
	private int numberCleanDesks;
	private int numberDirtyDesks;
	
	private final Lock lock = new ReentrantLock(true);
	private final Condition hasCleanDesks = lock.newCondition();
	private final Condition hasDirtyDesks = lock.newCondition();
	
	public OpenOffice(int numCleanDesks, int numDirtyDesks) 
	{
		this.numberCleanDesks = numCleanDesks;
		this.numberDirtyDesks = numDirtyDesks;
	}
	
	// clerk obtains an available clean desk
	public Desk arrive()
	{
		lock.lock();
		
		try 
		{
			// While no clean desks are available, wait until a clean desk is available.
			while (numberCleanDesks == 0)
			{
				hasCleanDesks.await();
			}
			
			// A clean desk will be provided to clerk (no longer available in office).
			numberCleanDesks--;
		}
		catch (Exception e) 
		{ 
			System.out.println(e);
		}
		finally 
		{
			lock.unlock();
		}
		
		// Simulate returning a clean desk.
		return new Desk();
	}
	
	// clerk leaves the desk (now dirty)
	public void leave(Desk desk)
	{
		lock.lock();
		
		try 
		{
			desk.makeDirty();
			numberDirtyDesks++;
			hasDirtyDesks.signal();
		}
		catch (Exception e)
		{
			System.out.println(e);
		}
		finally
		{
			lock.unlock();
		}
	}
	
	// cleaner gets a dirty desk to clean
	public Desk service()
	{
		lock.lock();
		
		try 
		{
			// While there are no dirty desks to clean, wait for a dirty desk to be available.
			while (numberDirtyDesks == 0) 
			{
				hasDirtyDesks.await();
			}
			
			// One less dirty desk available for cleaning.
			numberDirtyDesks--;
		}
		catch (Exception e)
		{
			System.out.println(e);
		}
		finally
		{
			lock.unlock();
		}
		
		// Give the dirty desk to the cleaner thread.
		Desk d = new Desk();
		d.makeDirty();
		return d;
	}
	
	// cleaner has finished cleaning the dirty desk
	public void cleaned(Desk desk)
	{
		lock.lock();
		
		try 
		{
			desk.clean();
			numberCleanDesks++;
			hasCleanDesks.signal();	
		}
		catch (Exception e)
		{
			System.out.println(e);
		}
		finally
		{
			lock.unlock();
		}
	}
}