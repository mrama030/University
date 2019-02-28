package Classes;

import java.util.*;

public class SimplePoolTree 
{
	// Root Attribute
    public SimplePoolTreeNode Root;

    // Empty Constructor
    public SimplePoolTree() { super();}

    // Pre-order traversal for the solution's list of names.
    public ArrayList<String> searchRouteNames(SimplePoolTreeNode rootNode)
    {
    	if(rootNode.Value == null)
    	{
    		return(null);
    	}
    	
    	ArrayList<String> solution = new ArrayList<String>();
    	
    	solution.add(rootNode.Value.Name);
    	
    	ArrayList<SimplePoolTreeNode> children = rootNode.getChildren();
    	
    	if (children != null)
    	{
    		for(SimplePoolTreeNode child : children) 
    		{
    			ArrayList<String> temp = searchRouteNames(child);
    			if (temp != null)
    			{
    				solution.addAll(temp);
    			}
    		}
    	}
    	
    	return (solution);
    }

    // Pre-order traversal for the solution's list of distances.
    public ArrayList<Double> searchRouteDistances(SimplePoolTreeNode rootNode)
    {
    	if(rootNode.Value == null)
    	{
    		return(null);
    	}
    	
    	ArrayList<Double> solution = new ArrayList<Double>();
    	
    	solution.add(rootNode.DistanceToParent);
    	
    	ArrayList<SimplePoolTreeNode> children = rootNode.getChildren();
    	
    	if (children != null)
    	{
    		for(SimplePoolTreeNode child : children) 
    		{
    			ArrayList<Double> temp = searchRouteDistances(child);
    			if (temp!= null)
    			{
    				solution.addAll(temp);
    			}
    		}
    	}
    	
    	return (solution);
    }  
}