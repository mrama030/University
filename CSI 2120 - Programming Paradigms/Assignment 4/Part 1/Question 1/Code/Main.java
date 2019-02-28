import java.util.*;
import java.io.*;
import java.text.DecimalFormat;
import Classes.SimplePool;
import Classes.SimplePoolTree;
import Classes.SimplePoolTreeNode;

public class Main 
{
	public static void main(String[] args) throws IOException
	{
		if (args.length < 1 || args == null)
		{
			System.out.print("Please close the program and try again while providing a path and file name.");
		}
		else
		{
			// 1. Obtain the sorted list from the input text file.
			
			File inputFile = new File(args[0]);
			BufferedReader br = new BufferedReader(new FileReader(inputFile));
			ArrayList<SimplePool> poolList = new ArrayList<SimplePool>();
			
			String temp1;
			String temp2;
			String temp3;
			while((temp1 = br.readLine()) != null && (temp2 = br.readLine()) != null && (temp3 = br.readLine()) != null)
			{
				SimplePool pool = new SimplePool(temp1.toString(), Double.parseDouble(temp2), Double.parseDouble(temp3));
				poolList.add(pool);
			}
			
			br.close();
			
			// 2. Build the tree
			
			// Create a tree.
			SimplePoolTree tree = new SimplePoolTree();
			// Create a root node.
			SimplePoolTreeNode root = new SimplePoolTreeNode();
			// Assign no distance to root node.
			root.DistanceToParent = 0.0;
			// Store the most western pool as the root node's value.
			root.Value = poolList.get(0);
			// Set the created node as the tree's root node.
			tree.Root = root;
		
			// Go through the sorted list of pools, excluding root.
			
			for (int z = 1; z < poolList.size(); z++)
			{				
				// For each element (from left to right in the list),
				// search for the minimum distance parent, which must already be in the tree
				// (located to the left of the current element) in the poolList.
				
				int closestParentIndex = 0;
				double minimumDistance = 9999999999999.0;
				double tempDistance = 0.0;
				
				// Find the index of the closest parent.
				for (int q = 0; q < z; q++)
				{					
					tempDistance = poolList.get(0).calculateDistance(poolList.get(z), poolList.get(q));
					
					if (Double.compare(tempDistance, minimumDistance) < 0)
					{
						minimumDistance = tempDistance;
						closestParentIndex = q;
					}
				}
				
				// Obtain the closest parent node.
				SimplePoolTreeNode parentNode = tree.Root.find(tree, poolList.get(closestParentIndex).Name);
				// Create the childNode to add to the closest parent.
				SimplePoolTreeNode ch = new SimplePoolTreeNode(poolList.get(z), minimumDistance);
				// Add child to the parent.
				parentNode.addChild(ch);
			}
			
			// 3. Traverse tree, obtain results lists and print results to a text file
			double totalDistance = 0.0;
			ArrayList<Double> distances = tree.searchRouteDistances(tree.Root);
			ArrayList<String> names = tree.searchRouteNames(tree.Root);
			
			BufferedWriter writter = new BufferedWriter(new FileWriter("solution.txt"));
			DecimalFormat decimalFormat = new DecimalFormat("#0.000");
			
			for (int x=0; x < names.size(); x++)
			{
				totalDistance += distances.get(x); 
				// Write to text file
				writter.write(names.get(x) + " " + decimalFormat.format(totalDistance) + "\n");
			}
			writter.close();
		}
	}
}