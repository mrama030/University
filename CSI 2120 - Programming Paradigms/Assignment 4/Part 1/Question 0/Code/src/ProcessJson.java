import com.fasterxml.jackson.core.JsonParseException;
import com.fasterxml.jackson.databind.JsonMappingException;
import com.fasterxml.jackson.databind.ObjectMapper;
import com.fasterxml.jackson.databind.DeserializationFeature;
import java.io.File;
import java.io.IOException;
import Classes.Pools;
import Classes.SimplePool;
import java.io.*;
import java.util.*;

public class ProcessJson
{
	public static void main(String[] args) throws JsonParseException, JsonMappingException, IOException
	{
		File jsonFile = new File("src/wading-pools2.json");
		ObjectMapper mapper = new ObjectMapper();
		mapper.configure(DeserializationFeature.FAIL_ON_UNKNOWN_PROPERTIES, false);
		
		Pools p = null;
		p = mapper.readValue(jsonFile, Pools.class);
		
		try 
		{
			ArrayList<SimplePool> simplePoolsList = new ArrayList<SimplePool>();
			
			for (int z=0; z < 62; z++)
			{
				SimplePool temp = new SimplePool(p.getPools(z).getName().replace("Wading Pool - ", ""), p.getPools(z).getLatitude(), p.getPools(z).getLongitude());
				simplePoolsList.add(temp);
			}
			
			// Professor indicated we can perform the sorting from west to east in the java preprocessing phase.
			Collections.sort(simplePoolsList);
			
			// Generate a text file for Java, Scheme and Go.
			BufferedWriter writter = new BufferedWriter(new FileWriter("ParsedPools.txt"));
			for (int z=0; z < 62; z++)
			{
				// Print to console (unsorted)
				//System.out.println(p.getPools(z).getName()+"\n");
				//System.out.println(p.getPools(z).getLatitude()+"\n");
				//System.out.println(p.getPools(z).getLongitude()+"\n");
				
				//Write to text file
				writter.write(simplePoolsList.get(z).Name+"\n");
				writter.write(simplePoolsList.get(z).Latitude+"\n");
				writter.write(simplePoolsList.get(z).Longitude+"");
				if (z != 61)
					writter.write("\n");
			}
			writter.close();
			
			
			// Generate a Prolog Database which will have predicates added to it later.
			BufferedWriter writter2 = new BufferedWriter(new FileWriter("FindRoute.pl"));
			String prolog = "sortedPoolList(Spl) :- Spl=[";
			
			for (int z=0; z < 62; z++)
			{
				prolog += "[";
				prolog += "\"" + simplePoolsList.get(z).Name+"\",";
				prolog += simplePoolsList.get(z).Latitude+",";
				prolog += simplePoolsList.get(z).Longitude+"";
				prolog += "]";
				if (z != 61)
					prolog += ",";
			}
			
			prolog += "].";
			writter2.write(prolog);
			writter2.close();
        } catch (IOException e) {}  
	}
}