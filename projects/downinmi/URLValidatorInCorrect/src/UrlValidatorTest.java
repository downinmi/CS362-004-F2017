/*
 * Licensed to the Apache Software Foundation (ASF) under one or more
 * contributor license agreements.  See the NOTICE file distributed with
 * this work for additional information regarding copyright ownership.
 * The ASF licenses this file to You under the Apache License, Version 2.0
 * (the "License"); you may not use this file except in compliance with
 * the License.  You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */


import junit.framework.TestCase;
import java.util.Random;




/**
 * Performs Validation Test for url validations.
 *
 * @version $Revision: 1128446 $ $Date: 2011-05-27 13:29:27 -0700 (Fri, 27 May 2011) $
 */
public class UrlValidatorTest extends TestCase {

   private boolean printStatus = false;
   private boolean printIndex = false;//print index that indicates current scheme,host,port,path, query test were using.

   public UrlValidatorTest(String testName) {
      super(testName);
   }

   
   
   public void testManualTest()
   {
	   System.out.println("Starting Manual Testing");
	   UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
	   System.out.println(urlVal.isValid("http://www.amazon.com")); //true
	   System.out.println(urlVal.isValid("http://www..amazon.com")); //false
	   System.out.println(urlVal.isValid("http:///www.amazon.com")); //false
	   System.out.println(urlVal.isValid("http:255.255.255.255")); //false
	   System.out.println(urlVal.isValid("http://255.255.255.255")); //true
	   System.out.println(urlVal.isValid("http://www.amazon.com:80")); //true
	   System.out.println(urlVal.isValid("http://www.amazon.com:80/test1/file")); //true
	   System.out.println(urlVal.isValid("http://www.amazon.com?action=view")); //false, but should return true
	   System.out.println(urlVal.isValid("http://www.amazon.com?action=edit&mode=up")); //false, but should return true
	   System.out.println(urlVal.isValid("http://www.amazon.com:80?action=view")); //false, but should return true
	   System.out.println(urlVal.isValid("http://www.amazon.com/../")); //false
	   System.out.println(urlVal.isValid("http://www.google.com/../")); //false
	   System.out.println(urlVal.isValid("http://www.google.com:65a")); //false
	   System.out.println(urlVal.isValid("https://www.google.com:65a")); //false
	   System.out.println(urlVal.isValid("h3t://www.google.com:65a")); //false
	   System.out.println(urlVal.isValid("3ht://www.google.com:65a")); //false
	   System.out.println(urlVal.isValid("http:/www.google.com:65a")); //false
	   System.out.println(urlVal.isValid("http/www.google.com:65a")); //false
	   System.out.println(urlVal.isValid("www.google.com:65a")); //false
	   System.out.println(urlVal.isValid("www.google.com")); //false, but should return true
	   System.out.println(urlVal.isValid("www.amazon.com")); //false, but should return true
	   System.out.println("\n");
   }
   
   //Maybe partition based on URLs that are just one off being correct and their correct count part?
   //EX: http:/www.amazon.com and http://www.amazon.com
   //We could do this with each of the 5 URL parts
   //This could test some sort of boundary values
   //We could also test URLs with one of the 5 URL parts being incorrect
   //EX: http://www..amazon.com and http://www.amazon.com:65a
   
   //valid partition
   public void testYourFirstPartition()
   {
	   System.out.println("Starting First Partition");
	   UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
	   System.out.println(urlVal.isValid("http://www.amazon.com:80/test")); //true
	   System.out.println(urlVal.isValid("http://www.amazon.com:0?action=edit&mode=up")); //true
	   System.out.println(urlVal.isValid("http://www.amazon.com:0?action=edit&mode=up")); //true
	   System.out.println(urlVal.isValid("ftp://www.google.com:65535")); //true
	   System.out.println(urlVal.isValid("https://www.google.com:65535")); //true
	   System.out.println(urlVal.isValid("h3t://www.google.com:65535")); //true
	   System.out.println(urlVal.isValid("http://www.facebook.com")); //true
	   System.out.println(urlVal.isValid("https://www.facebook.com")); //true
	   System.out.println(urlVal.isValid("https://www.facebook.com?action=view")); //true
	   System.out.println("\n");
   }
   
   //invalid partition
   public void testYourSecondPartition(){
	   System.out.println("Starting Second Partition");
	   UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
	   System.out.println(urlVal.isValid("http:/www.amazon.com")); //false
	   System.out.println(urlVal.isValid("htp://www.amazon.com")); //false
	   System.out.println(urlVal.isValid("http://wwww.amazon.com")); //false
	   System.out.println(urlVal.isValid("http://ww.facebook.com")); //false
	   System.out.println(urlVal.isValid("http://www..google.com")); //false
	   System.out.println(urlVal.isValid("http://www.google.com:80a")); //false
	   System.out.println(urlVal.isValid("http://www.google.com:80testing123")); //false
	   System.out.println(urlVal.isValid("http://www.google.com:80param?=&valid?param&=valid")); //false
	   System.out.println(urlVal.isValid("http://www.google.com:80?&=+?&")); //false
	   System.out.println(urlVal.isValid("http://www.facebook.com/..")); //false
	   System.out.println(urlVal.isValid("http://www.facebook.com/..//test")); //false
	   System.out.println(urlVal.isValid("http://www.facebook.com/../test")); //false
	   System.out.println(urlVal.isValid("http://www.amazon.com:-1")); //false
	   System.out.println("\n");
   }
   
   //Two options:
   //1. Go through every combination of URL parts that we add to  the results pair arrays
   //2. Randomly choose 10000 combinations of URL parts from our arrays
   public void testIsValid(Object[] testObjects)
   {
	   Random rand = new Random();
	   final int SCHEME_INDEX= 0;
	   final int AUTH_INDEX = 1;
	   final int PORT_INDEX = 2;
	   final int PATH_INDEX = 3;
	   final int QUERY_INDEX = 4;
	   
	  ResultPair[] schemes = (ResultPair[]) testObjects[SCHEME_INDEX];
	  ResultPair[] authorities = (ResultPair[]) testObjects[AUTH_INDEX];
	  ResultPair[] ports = (ResultPair[]) testObjects[PORT_INDEX];
	  ResultPair[] paths = (ResultPair[]) testObjects[PATH_INDEX];
	  ResultPair[] queries = (ResultPair[]) testObjects[QUERY_INDEX];

	   UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);

	   
	   for(int i = 0; i < 10000; i++)
	   {
	 	  ResultPair scheme = schemes[rand.nextInt(schemes.length)];
	 	  ResultPair auth = authorities[rand.nextInt(authorities.length)];
	 	  ResultPair port = ports[rand.nextInt(ports.length)];
	 	  ResultPair path = paths[rand.nextInt(paths.length)];
	 	  ResultPair query = queries[rand.nextInt(queries.length)];

	 	  boolean valid = scheme.valid && auth.valid && port.valid && path.valid && query.valid;
	 	  String url = scheme.item + auth.item + port.item + path.item + query.item;
	 	  if(urlVal.isValid(url) != valid)
	 	  {
		 	  System.out.println("\"" + url + "\"");
		 	  System.out.println("Result:" + urlVal.isValid(url) + " Expected:" + valid);
		 	  System.out.println("ResultPairs input:");
		 	  System.out.println("   \"" + scheme.item + "\", " + scheme.valid);
		 	  System.out.println("   \"" + auth.item + "\", " + auth.valid);
		 	  System.out.println("   \"" + port.item + "\", " + port.valid);
		 	  System.out.println("   \"" + path.item + "\", " + path.valid);
		 	  System.out.println("   \"" + query.item + "\", " + query.valid);
		 	  System.out.println("\n");
	 		  
	 	  }
	 	  //assert(urlVal.isValid(url) ==  valid);
	   }   
   }
   
   public void testAnyOtherUnitTest()
   {
	   
   
   /**
    * Create set of tests by taking the testUrlXXX arrays and
    * running through all possible permutations of their combinations.
    *
    * @param testObjects Used to create a url.
    */
   //Need to add more values here
   ResultPair[] testUrlScheme = {new ResultPair("http://", true),
		   new ResultPair("https://", true),
		   new ResultPair("ftp://", true),
		   new ResultPair("http:/", false),
		   new ResultPair("http//", false)};
   ResultPair[] testUrlAuthority = {new ResultPair("www.google.com", true),
		   new ResultPair("www..google.com", false),
		   new ResultPair("www.amazon.com", true),
		   new ResultPair("www.facebook.com", true),
		   new ResultPair("ww.google.com", false),
		   new ResultPair("www.google.c", false),
		   new ResultPair("www.google..com", false),
		   new ResultPair("www/google.com", false)};
   ResultPair[] testUrlPort = {new ResultPair(":80", true)};
   ResultPair[] testPath = {new ResultPair("/test1", true)};
   ResultPair[] testUrlQuery = {new ResultPair("?action=view", true)};
   
   //what we will pass to testIsValid
   Object[] testUrlParts = {testUrlScheme, testUrlAuthority, testUrlPort, testPath, testUrlQuery};
   int[] testPartsIndex = {0, 0, 0, 0, 0};
   
   System.out.println("Starting testAnyOtherUnitTest... ");

   testIsValid(testUrlParts);
}
}
