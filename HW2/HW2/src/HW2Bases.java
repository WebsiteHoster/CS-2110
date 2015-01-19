/**
 * CS 2110 Spring 2015 HW2
 * Part 1 - Coding with bases
 * 
 * @author Jesse Chen
 *
 * Global rules for this file:
 * - You may not use more than 2 conditionals per method. Conditionals are
 *   if-statements, if-else statements, or ternary expressions. The else block
 *   associated with an if-statement does not count toward this sum.
 * - You may not use more than 2 looping constructs per method. Looping
 *   constructs include for loops, while loops and do-while loops.
 * - You may not use nested loops.
 * - You may not declare any file-level variables.
 * - You may not declare any objects, other than String in select methods.
 * - You may not use switch statements.
 * - You may not use the unsigned right shift operator (>>>)
 * - You may not write any helper methods, or call any other method from this or
 *   another file to implement any method.
 * - The only Java API methods you are allowed to invoke are:
 *     String.length()
 *     String.charAt()
 *     String.equals()
 * - You may not invoke the above methods from string literals.
 *     Example: "12345".length()
 * - When concatenating numbers with Strings, you may only do so if the number
 *   is a single digit.
 *
 * Method-specific rules for this file:
 * - You may not use multiplication, division or modulus in any method, EXCEPT
 *   strdtoi.
 * - You may declare exactly one String variable each in itostrb, and itostrx.
 */
public class HW2Bases
{
	
	public static void main(String[] args) {
		itostrb(0xFEED);
    }
	
	/**
	 * strdtoi - Decimal String to int
	 *
	 * Convert a string containing ASCII characters (in decimal) to an int.
	 * You do not have to handle negative numbers. The Strings we will pass in will be
	 * valid decimal numbers, and able to fit in a 32-bit signed integer.
	 * 
	 * Example: strdtoi("123"); // => 123
	 */
	public static int strdtoi(String decimal)
	{
		//System.out.println("Testing " + decimal);
		int result = 0;
		int curr = 0;
		int mult = 1;
		
		for (int i = decimal.length() - 1; i >= 0; i--) {
			curr = decimal.charAt(i) - '0';
			//System.out.println("curr = " + curr);
			result += curr * mult;
			mult *= 10;
			//System.out.println(result);
		}
		
		return result;
	}

	/**
	 * strbtoi - Binary String to int
	 *
	 * Convert a string containing ASCII characters (in binary) to an int.
	 * You do not have to handle negative numbers. The Strings we will pass in will be
	 * valid binary numbers, and able to fit in a 32-bit signed integer.
	 * 
	 * Example: strbtoi("111"); // => 7
	 */
	public static int strbtoi(String binary)
	{
		//System.out.println(binary);
		
		int result = 0;
		
		for (int i = 0; i < binary.length(); i++) {
			char curr = binary.charAt(i); 
			//System.out.println("Current bit: " + curr);
			
			if (curr == '1') {
				result = (result << 1) | 0x1;	//Multiply by 2 then add 1
			} else if (curr == '0') {
				result <<= 1;					//Multiply by 2
			}
			
			//System.out.println("Result: " + result);
		}
		
		return result;
	}

	/**
	 * strxtoi - Hexadecimal String to int
	 *
	 * Convert a string containing ASCII characters (in hex) to an int.
	 * The input string will only contain numbers and uppercase letters A-F.
	 * You do not have to handle negative numbers. The Strings we will pass in will be
	 * valid hexadecimal numbers, and able to fit in a 32-bit signed integer.
	 * 
	 * Example: strxtoi("A6"); // => 166
	 */
	public static int strxtoi(String hex)
	{
		//System.out.println(hex);
		
		int result = 0;
		int shift = 0;
		
		for (int i = hex.length() - 1; i >= 0 ; i--) {
			char curr = hex.charAt(i);
			int value = 0;
			
			//System.out.println("Current bit: " + curr + ", " + (int)curr);
			
			if (curr >= 48 && curr <= 57) {
				value = curr - 48;
			} else if (curr >= 65 && curr <= 70) {
				value = curr - 55;
			}
			
			value <<= shift;
			result += value;
			shift += 4;
			
			//System.out.println("Result: " + result);
		}
		
		return result;
	}

	/**
	 * itostrb - int to Binary String
	 *
	 * Convert a int into a String containing ASCII characters (in binary).
	 * You do not have to handle negative numbers.
	 * The String returned should contain the minimum number of characters necessary to
	 * represent the number that was passed in.
	 * 
	 * Example: itostrb(7); // => "111"
	 */
	public static String itostrb(int binary)
	{
		String result = "";
		//System.out.println(binary);
		
		do {
			if ((binary & 0x1) == 1) {
				result = "1" + result;
			} else {
				result = "0" + result;
			}
			
			binary >>= 1;
			
			//System.out.println("n = " + binary);
			//System.out.println("result = " + result);
		} while (binary > 0);
		
		return result;
	}

	/**
	 * itostrx - int to Hexadecimal String
	 *
	 * Convert a int into a String containing ASCII characters (in hexadecimal).
	 * The output string should only contain numbers and uppercase letters A-F.
	 * You do not have to handle negative numbers.
	 * The String returned should contain the minimum number of characters necessary to
	 * represent the number that was passed in.
	 * 
	 * Example: itostrx(166); // => "A6"
	 */
	public static String itostrx(int hex)
	{
		String result = "";
		//System.out.println(hex);
		
		do {
			if ((hex & 0x1) == 1) {
				result = "1" + result;
			} else {
				result = "0" + result;
			}
			
			hex >>= 1;
			
			//System.out.println("n = " + hex);
			//System.out.println("result = " + result);
		} while (hex > 0);
		
		return result;
	}
}
