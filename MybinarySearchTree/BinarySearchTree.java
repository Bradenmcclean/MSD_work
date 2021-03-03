package assignment05;

import java.util.ArrayList;
import java.util.Collection;

import java.util.NoSuchElementException;

public class BinarySearchTree<T extends Comparable<? super T>> implements SortedSet<T>
{
	BinaryNode root=null;
	int size=0;

	
	public class BinaryNode
	{
		T data;
		BinaryNode left;
		BinaryNode right;
		
		BinaryNode(T dataIn)
		{
			left=null;
			right=null;
			data=dataIn;
		}
		
	}
	
	public BinaryNode successorFinder(BinaryNode theNode)
	{
		BinaryNode temp=theNode.right;
		while (temp.left!=null)
		{
			temp=temp.left;
			
		}
		System.out.println(temp.data+" WAS SELECTED");
		return temp;
	}
	
	
	////Recursive tinyArray Function for toArray
	public void tinyArray(BinaryNode theNode,ArrayList<T> theList)
	{
		if (theNode==null)
		{
			return;
		}
		theList.add(theNode.data);
		tinyArray(theNode.left,theList);
		tinyArray(theNode.right,theList);
		
	}
	//Recursive tinyContains Function for Contains
	public void tinyRemove(BinaryNode theNode,T item)
	{
		
		
		if(!(theNode.right==null))
		{
			//checking right side
			 if (theNode.right.data.equals(item))
			{
				//case 1
				if ((theNode.right.right==null)&(theNode.right.left==null))
				{
					System.out.println(theNode.right.data+" was deleted");
					theNode.right=null;
				}
				//Case 2 right not null
				else if ((theNode.right.right!=null)&(theNode.right.left==null))
				{
					System.out.println(theNode.right.data+" was deleted and "+ theNode.right.right.data+"is now right");
					
					theNode.right=theNode.right.right;
				}
				//Case 2 left not null
				else if ((theNode.right.right==null)&(theNode.right.left!=null))
				{
					System.out.println(theNode.right.data+" was deleted and "+ theNode.right.left.data+"is now right");
					theNode.right=theNode.right.left;
				}
				//CASE 3 MADDNESS BABY
				else
				{
					T Successordata=successorFinder(theNode.right).data;
					 
					 this.remove(Successordata);
					 theNode.right.data=Successordata;
					 System.out.println(theNode.right.data+" is  now succeded");
					 
					
				}
				
				return;
				
			}
			
		}
		
		
		
		if(!(theNode.left==(null)))
		{
		//will be left side
		 if(theNode.left.data.equals(item))
		 {
			//case 1
			if ((theNode.left.right==null)&(theNode.left.left==null))
			{
				System.out.println(theNode.left.data+" was deleted");
				theNode.left=null;
			}
			//Case 2 right not null
			else if ((theNode.left.right!=null)&(theNode.left.left==null))
			{
				System.out.println(theNode.left.data+" was deleted and "+ theNode.left.right.data+"is now left");
				theNode.left=theNode.left.right;
			}
			//Case 2 left not null
			else if ((theNode.left.right==null)&(theNode.left.left!=null))
			{
				System.out.println(theNode.left.data+" was deleted and "+ theNode.left.left.data+"is now left");
				theNode.left=theNode.left.left;
			}
			else
			{
				T Successordata=successorFinder(theNode.left).data;
				 
				 this.remove(Successordata);
				 
				 theNode.left.data=Successordata;
				 System.out.println(theNode.left.data+" is  now succeded");
				
			}
			return;
			
		 }
		}
		
		if(theNode.data.compareTo(item)>0)
		{
			
				System.out.println(theNode.data+" is going left for "+ item);
				tinyRemove(theNode.left,item);
			
		}
		else if(theNode.data.compareTo(item)<0)
		{
			
				System.out.println(theNode.data+" is going right for "+ item);
				tinyRemove(theNode.right,item);
			
		}
	

		return;
	
	}
	public Boolean tinyContain(BinaryNode theNode,T item,Boolean flag)
	{
		
		
		if(theNode.data.compareTo(item)>0)
		{
			if (theNode.left==null)
			{
				flag=false;
				return false;	
			}
			else
			{
//				System.out.println(theNode.data+" is going left for "+ item);
				flag=tinyContain(theNode.left,item,flag);
			}
		}
		else if(theNode.data.compareTo(item)<0)
		{
			if (theNode.right==null)
			{
				flag=false;
				return false;	
			}
			else
			{
//				System.out.println(theNode.data+" is going right for "+ item);
				flag=tinyContain(theNode.right,item,flag);
			}
		}
		else 
		{
//			System.out.println("hello");
			flag=true;
			return true;
		}
	return flag;
	}
	//Recursive insertion Function for adds
	public void insertion(BinaryNode theNode,T item)
	{
	
		if(theNode.data.compareTo(item)>0)
		{
			if (theNode.left==null)
			{
//				System.out.println(theNode.data+" HAS A LEFT OF "+ item);
				theNode.left=new BinaryNode(item);
			}
			else
			{
				insertion(theNode.left,item);
			}
		}
		else
		{
			if (theNode.right==null)
			{
//				System.out.println(theNode.data+" HAS A RIGHT OF "+ item);
				theNode.right=new BinaryNode(item);
			}
			else
			{
				insertion(theNode.right,item);
			}
		}
	
	}

	@Override
	public boolean add(T item)throws NullPointerException
	{
		if (item==null)
		{
			throw new NullPointerException();
		}
		
		
		if (root==null)
		{
			BinaryNode temp =new BinaryNode(item);
			root=temp;
			size++;
			return true;
		}
		else
		{
			insertion(root,item);
			size++;
			return true;
				
		}
	}

	@Override
	public boolean addAll(Collection<? extends T> items) 	
	{
		
		boolean flag=true;
		for (T e:items)
		{
			if (!this.contains(e))
			{
				flag=false;
			}
			this.add(e);
			
		}
		return flag;
}

	@Override
	public void clear()
	{
		root=null;
		
	}

	@Override
	public boolean contains(T item) throws NullPointerException
	{
		if (item==null)
		{
			throw new NullPointerException();
		}
		
		
		if (isEmpty())
		{
			return false;
		}
		Boolean flag=null;
		
		return tinyContain(root,item,flag);
	}

	@Override
	public boolean containsAll(Collection<? extends T> items) {
		boolean flag2=true;
		for (T e:items)
		{
			if (!this.contains(e))
			{
				flag2=false;
			}
			
		}
		return flag2;
	}

	@Override
	public T first() throws NoSuchElementException 
	{
		if (isEmpty())
		{
			throw new NoSuchElementException();
		}
		BinaryNode temp1=root;
		while(temp1.left!=null)
		{
			temp1=temp1.left;
		}
		return temp1.data;
		
	}

	@Override
	public boolean isEmpty() {
		if (root==null)
		{
		return true;
		}
		else 
		{
		return false;
		}
	}

	@Override
	public T last() throws NoSuchElementException
	{
		if (isEmpty())
		{
			throw new NoSuchElementException();
		}
		BinaryNode temp1=root;
		while(temp1.right!=null)
		{
			temp1=temp1.right;
		}
		return temp1.data;
	}

	@Override
	public boolean remove(T item) throws NullPointerException
	{
		if (item==null)
		{
			throw new NullPointerException();
		}
		if (contains(item))
		{
			tinyRemove(root,item);
			return true;
		}
		return false;
	}

	@Override
	public boolean removeAll(Collection<? extends T> items) 
	{
		
			boolean flag=true;
			for (T e:items)
			{
				if (!this.contains(e))
				{
					flag=false;
				}
				this.remove(e);
				
			}
			return flag;
	}


	@Override
	public int size() {
		// TODO Auto-generated method stub
		return size;
	}

	@Override
	public ArrayList<T> toArrayList() 
	{
		ArrayList<T> theList=new ArrayList<T>();
		if(!isEmpty())
		{
		tinyArray(root,theList);
		}
		return theList;
	}

}
