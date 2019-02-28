package Classes;

import java.util.*;

public class SimplePoolTreeNode
{
	// Attributes
	public SimplePoolTreeNode Parent;
    public SimplePool Value;
    private ArrayList<SimplePoolTreeNode> Children;
    public double DistanceToParent; // like an edge weight

    // Constructors
    public SimplePoolTreeNode() 
    {
        super();
        this.Children = new ArrayList<SimplePoolTreeNode>();
    }
    public SimplePoolTreeNode(SimplePool pool, double distanceToParent) 
    {
    	super();
        this.Children = new ArrayList<SimplePoolTreeNode>();
        this.Value = pool; 
        this.DistanceToParent = distanceToParent;
    }

    // Setters and Getters for Children
    public void setChildren(ArrayList<SimplePoolTreeNode> children) 
    {
        for(SimplePoolTreeNode child : children) 
        {
           child.Parent = this;
        }

        this.Children = children;
    }
    public ArrayList<SimplePoolTreeNode> getChildren() 
    {
        return(this.Children);
    }

    // Add Child to a Node.
    public void addChild(SimplePoolTreeNode child) 
    {
        child.Parent = this;
        this.Children.add(child);
    }
    
    // Used to find the node in the tree which is being built.
    public SimplePoolTreeNode find(SimplePoolTree tree, String poolName) 
    {
    	SimplePoolTreeNode result = null;

        if(tree.Root != null) 
        {
            result = recursiveFind(tree.Root, poolName);
        }

        return result;
    }

    private SimplePoolTreeNode recursiveFind(SimplePoolTreeNode currentNode, String poolName)
    {
    	SimplePoolTreeNode result = null;

        if (currentNode.Value.Name.equals(poolName)) 
        {
            result = currentNode;
        }
        else if (currentNode.getChildren() != null) 
        {
            int i = 0;
            while(result == null && i < currentNode.getChildren().size()) 
            {
                result = recursiveFind(currentNode.getChildren().get(i), poolName);
                i++;
            }
        }

        return result;
    }    
}