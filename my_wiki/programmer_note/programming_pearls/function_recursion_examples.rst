Function Recursion Samples
==========================

.. code-block:: c
   
   /* time complexity O(2^n)*/
   int arrayMaxVal(int array[], int n)
   {
       if(n == 1) 
           return array[0];
   
       if (array[0] >= arrayMaxVal(array+1, n-1))
           return array[0];
       else
           return  arrayMaxVal(array+1, n-1);
   }

   void reverser(char *s, int l, int r)
   {
       if(l < r)
       {
           char tmp = s[r];
           s[r] = s[l];
           s[l] = tmp;
           reverser(s, l+1, r-1);
       }
   }
   
   void reverse(char *s)
   {
       reverser(s, 0, strlen(s)-1);
   }

   /* itoa */
   void trans(int n)
   {
       int i = n % 10;
   
       if(n/10 > 0)
           trans(n/10); 
   
       printf("%c", i + '0');
   }

   /* rotate */
   void loopMove(char *str, int n)
   {
       int i,j,strLength;
       char tmp;
       strLength = strlen(str);
       for(i=0;i<n;i++)
       {
           tmp = str[strLength-1];              
           for(j=0; j<strLength-1; j++)
           {
               str[strLength-j-1] = str[strLength-j-2];  
           }
           str[0] = tmp;             
       }
   }