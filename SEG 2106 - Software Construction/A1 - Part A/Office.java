// Mohamed Ali Ramadan (7688825)
// SEG 2106 - Assignment 4: Part A

public interface Office 
{
	Desk arrive(); // clerk obtain an available clean desk
	void leave (Desk desk); // clerk leaves the desk (now dirty)
	Desk service(); // cleaner gets a desk to clean
	void cleaned(Desk desk); // cleaner has finished cleaning the desk
}
