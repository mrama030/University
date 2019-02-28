package Classes;

public class SimplePool
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
	
	public double calculateDistance(SimplePool poolOne, SimplePool poolTwo)
	{
		double lat1Rad = 180*(poolOne.Latitude/Math.PI);
		double lon1Rad = 180*(poolOne.Longitude/Math.PI);
		double lat2Rad = 180*(poolTwo.Latitude/Math.PI);
		double lon2Rad = 180*(poolTwo.Longitude/Math.PI);
		
		double A = Math.pow(Math.sin( (lat1Rad - lat2Rad)/2 ), 2);
		double C = Math.cos(lat1Rad)*Math.cos(lat2Rad);
		double Dx = Math.pow(Math.sin( (lon1Rad - lon2Rad)/2 ), 2);
		double B = C*Dx;
		double dRadians = 2*Math.asin(Math.sqrt(A+B));
		return (6371.0*dRadians);
	}
}


