import java.util.*;
import java.io.*;
public class readfiles
{
	public static void main(String[] args)
	{

		try
		{

			FileInputStream strm = new FileInputStream("readfile.txt");
			InputStreamReader in_str = new InputStreamReader(strm);

			int t;
			int charcount=0;
 			int wordcount=0;
 			int linecount=0;
			String stack="";
			LinkedList<String> list =new LinkedList<>();
			while((t=in_str.read())!= -1)
			{
			    	char r = (char)t;
				if(r==' '|| r==',')
                                                                {
                                                           		list.add(stack);
 					stack="";
                   				wordcount++;
                                                                 }
    				else if(r=='\n')
                                                                {
                                                     		list.add(stack);
 					stack="";
                   				wordcount++;
					linecount++;
     				}
				else
				{
					stack+=r;
                                                                                charcount++;
				}
			}
			System.out.println(charcount);
			System.out.println(wordcount);
			System.out.println(linecount);
			System.out.println(list);
			for(String s:list)
                                                {
				System.out.println(s);
                                                 }
			in_str.close();
			strm.close();
		}
		catch (FileNotFoundException fnfe)
		{
			System.out.println("NO Such File Exists");
		}
		catch (IOException except)
		{
			System.out.println("IOException occurred");
		}
	}
}
