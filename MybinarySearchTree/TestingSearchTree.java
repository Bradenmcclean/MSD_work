package assignment05;

import static org.junit.Assert.*;

import org.junit.After;
import org.junit.Assert;
import org.junit.Before;
import org.junit.Test;

import assignment03.BinarySearchSet;
import java.util.ArrayList;
public class TestingSearchTree 
{

	BinarySearchTree<String> stringsTestBoi= new BinarySearchTree<String>();
	BinarySearchTree<Integer> intsTestBoi;
	BinarySearchTree<Integer> intsTestBoi2=new BinarySearchTree<Integer>();
	BinarySearchTree<Integer> empty=new BinarySearchTree<Integer>();
	BinarySearchTree<Integer> justARoot=new BinarySearchTree<Integer>();
	 @Before
	   public void setUp() throws Exception 
	   {
		 intsTestBoi = new BinarySearchTree<Integer>();
		 stringsTestBoi.add("brad");
		 stringsTestBoi.add("kristie");
		 stringsTestBoi.add("animal");
		 stringsTestBoi.add("zeta");
		 stringsTestBoi.add("marlee");
		 stringsTestBoi.add("denver");
		 stringsTestBoi.add("tammy");
		 stringsTestBoi.add("ray");
		 intsTestBoi.add(6);
		 intsTestBoi.add(8);
		 intsTestBoi.add(7); 
		 intsTestBoi.add(5);
		 intsTestBoi.add(9);
		 intsTestBoi.add(2);
		 
		 intsTestBoi.add(4);
		 intsTestBoi.add(1);
		 intsTestBoi.add(4);
		 intsTestBoi.add(3);
		 justARoot.add(69);
		 
	   }

	   @After
	   public void tearDown() throws Exception 
	   {
		
	   }
	@Test
	public void checkingAdd() 
	{
		Assert.assertTrue("brad".equals(stringsTestBoi.root.data));
//		Assert.assertTrue(8==(intsTestBoi.root.right.));
		
		Assert.assertTrue(intsTestBoi.add(0));
		
		
		//This Line Will throw an Error
//		intsTestBoi.add(null);
		
	}

	@Test
	public void testingFirst() 
	{
		 Assert.assertTrue(1==(intsTestBoi.first()));
		 Assert.assertTrue("animal".equals(stringsTestBoi.first()));
		 Assert.assertTrue(69==(justARoot.first()));
		 
//		//Will throw error
//		 Assert.assertTrue(1==(empty.first()));
	
	}
	@Test
	public void testingContains() 
	{
		 Assert.assertTrue(justARoot.contains(69));
		 Assert.assertTrue(intsTestBoi.contains(1));
		 Assert.assertTrue(stringsTestBoi.contains("ray"));
		 
		
	
	}
	@Test
	public void testingLast() 
	{
		 Assert.assertTrue(9==(intsTestBoi.last()));
		 Assert.assertTrue("zeta".equals(stringsTestBoi.last()));
		 Assert.assertTrue(69==(justARoot.last()));
//		 //Will throw error
//		 Assert.assertTrue(2==(empty.last()));
	
	}
	@Test
	public void size() 
	{
		Assert.assertTrue(1==(justARoot.size()));
		Assert.assertTrue(10==(intsTestBoi.size()));
	
	}
	@Test
	public void ArrayList() 
	{
		
		ArrayList<Integer> testArray= intsTestBoi.toArrayList();
		for (int e:testArray)
		{
			System.out.println(e);
		}
	
	}
	@Test
	public void removeCase2() 
	{
	
		
//		//test left.right
//		intsTestBoi.add(16);
//		intsTestBoi.add(13);
//		intsTestBoi.add(11);
//		intsTestBoi.add(12);
//		intsTestBoi.remove(11);
		
//		//test left.left
//		intsTestBoi.add(16);
//		intsTestBoi.add(13);
//		intsTestBoi.add(11);
//		intsTestBoi.add(10);
//		intsTestBoi.remove(11);
		
//		//test right.left
//		intsTestBoi.add(16);
//		intsTestBoi.add(13);
//		intsTestBoi.add(14);
//		intsTestBoi.add(15);
//		intsTestBoi.remove(14);
		
//		//test right.right
//		intsTestBoi.add(16);
//		intsTestBoi.add(13);
//		intsTestBoi.add(15);
//		intsTestBoi.add(14);
//		intsTestBoi.remove(15);
	
	}
	@Test
	public void removeCase3() 
	{
		
		intsTestBoi.remove(2);
	
	}
//	@Test
//	public void removeCase1() 
//	{
//		
//		intsTestBoi.remove(9);
//		intsTestBoi.remove(7);
//		intsTestBoi.remove(3);
//		intsTestBoi.remove(1);
//		
//	
//	}
//	


}
