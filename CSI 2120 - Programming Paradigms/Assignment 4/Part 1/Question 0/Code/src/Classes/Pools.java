package Classes;
import com.fasterxml.jackson.annotation.JsonIgnoreProperties;

@JsonIgnoreProperties(ignoreUnknown=true)
public class Pools
{
	Pool[] pools;
	
	public Pool getPools(int i)
	{
	    return this.pools[i];
	}
	public void setPools(Pool[] pools)
	{
	    this.pools = pools;
	}
	
	public static class Pool
	{
		private String name;
		private double[] coordinates;
		
		public String getName()
		{
		    return this.name;
		}
		public void setName(String name)
		{
		    this.name = name;
		}
		
		public double getLatitude()
		{
		    return this.coordinates[1];
		}
		public double getLongitude()
		{
		    return this.coordinates[0];
		}
		public void setCoordinates(double[] coordinates)
		{
		    this.coordinates = coordinates;
		}	
	}
}
