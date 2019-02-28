package Classes;

public class SimplePool implements Comparable<SimplePool>
{
	public String Name;
	public double Latitude;
	public double Longitude;
	
	public SimplePool(String name, double lat, double lon)
	{
		this.Name = name;
		this.Latitude = lat;
		this.Longitude = lon;
	}

	@Override
	public int compareTo(SimplePool otherPool) 
	{
		if (this.Longitude < otherPool.Longitude)
		{
			return (-1);
		}
		else if (this.Longitude == otherPool.Longitude)
		{
			return (0);
		}
		else if (this.Longitude > otherPool.Longitude)
		{
			return (1);
		}
		return(1);
	}
}
