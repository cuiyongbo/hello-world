******************************
Suffix sort by induced sorting
******************************

.. code-block:: python

   #!/usr/bin/env python
   
   def naivelyMakeSuffixArray(source):
   
       suffixes = []
       for offset in range(len(source)+1):
           suffixes.append(source[offset:])
   
       # worse-case running time complexity: O(n log n)
       suffixes.sort()
   
       suffixArray = []
       for suffix in suffixes:
           suffixArray.append(len(source) - len(suffix))
       return suffixArray
   
   S_TYPE = ord("S")
   L_TYPE = ord("L")
   
   def buildTypeMap(data):
   
       res = bytearray(len(data) + 1)
   
       res[-1] = S_TYPE
       res[-2] = L_TYPE
   
       # scan data from right to left
       # running time complexit: O(n)
       for i in range(len(data)-2, -1, -1):
           if(data[i] > data[i+1]):
               res[i] = L_TYPE
           elif data[i] == data[i+1] and res[i+1] == L_TYPE:
               res[i] = L_TYPE
           else:
               res[i] = S_TYPE
   
       return res
   
   def showTypeMap(data):
       print(data.decode("ascii"))
       print(buildTypeMap(data).decode("ascii"))
   
   
   def isLMSChar(offset, typeMap):
       if offset == 0:
           return False
       elif typeMap[offset] == S_TYPE and typeMap[offset-1] == L_TYPE:
           return True
       else:
           return False
   
   def showTypeMapWithLMSChar(data):
       typeMap = buildTypeMap(data)
   
       print(data.decode("ascii"))
       print(typeMap.decode("ascii"))
   
       print("".join(
               "^" if isLMSChar(i, typeMap) else " "
               for i in range(len(typeMap)) 
           ))
   
   def cmpLMSChar(string, typeMap, offsetA, offsetB):
       """
       Return  True if LMS substrings at offsetA and offsetB are equal.
       """
   
       if offsetA == len(string) or offsetB == len(string):
           return False
   
       i=0
       while True:
           aIsLMS = isLMSChar(i+offsetA, typeMap)
           bIsLMS = isLMSChar(i+offsetB, typeMap)
           if i>0 and aIsLMS and bIsLMS:
               return True
           elif aIsLMS != bIsLMS:
               return False
           elif string[i+offsetA] != string[i+offsetB]:
               return False
           else:
               i = i + 1
   
   def findBucketSizes(string, alphabetSize=256):
       res = [0]*alphabetSize
       for char in string:
           res[ord(char)] = res[ord(char)] + 1
       return res
   
   def findBucketHeads(bucketSizes):
       offset = 1
       res = []
       for size in bucketSizes:
           res.append(offset)
           offset = offset + size
       return res
   
   def findBucketTails(bucketSizes):
       offset = 0
       res = []
       for size in bucketSizes:
           offset = offset + size
           res.append(offset)
       return res
   
   def makeSuffixArrayByInducedSorting(string, alphabetSize):
       typeMap = buildTypeMap(string)
       bucketSizes = findBucketSizes(string, alphabetSize)
       guessedSuffixArray = guessLMSSort(string, bucketSizes, typeMap)
   
       induceSortL(string, guessedSuffixArray, bucketSizes, typeMap)
       induceSortS(string, guessedSuffixArray, bucketSizes, typeMap)
   
       summaryString, summaryAlphaBetSize, summarySuffixOffsets = \
           summariseSuffixArray(string, guessedSuffixArray, typeMap)
   
       summarySuffixArray = makeSummarySuffixArray(summaryString, summaryAlphaBetSize)
   
       result = accurateLMSSort(string, bucketSizes, typeMap, 
                           summarySuffixArray, summarySuffixOffsets)
   
       induceSortL(string, result, bucketSizes, typeMap)
       induceSortS(string, result, bucketSizes, typeMap)
       return result
   
   def showSuffixArray(array, pos=None):
       print("".join("%02d" % x for x in array))
       if pos is not None:
           print(" ".join(
               "^^" if x == pos else " "
               for x in range(len(array)))
           )
   
   def guessLMSSort(string, bucketSizes, typeMap):
       guessedSuffixArray = [-1] * (len(string)+1)
       bucketTails = findBucketTails(bucketSizes)
       #print bucketTails
       for i in range(len(string)):
           if not isLMSChar(i, typeMap):
               continue
           bucketIndex = ord(string[i])
           guessedSuffixArray[bucketTails[bucketIndex]] = i
           bucketTails[bucketIndex] -= 1
           showSuffixArray(guessedSuffixArray)
       guessedSuffixArray[0] = len(string)
       showSuffixArray(guessedSuffixArray)
       return guessedSuffixArray
   
   
   def induceSortL(string, guessedSuffixArray, bucketSizes, typeMap):
       bucketHeads = findBucketHeads(bucketSizes)
       print bucketHeads
       for i in range(len(guessedSuffixArray)):
           if guessedSuffixArray[i] == -1:
               continue 
           j = guessedSuffixArray[i] - 1
           if j < 0:
               continue
           if typeMap[j] != L_TYPE:
               continue
           bucketIndex = ord(string[j])
           guessedSuffixArray[bucketHeads[bucketIndex]] = j
           bucketHeads[bucketIndex] += 1
           showSuffixArray(guessedSuffixArray, i)
   
   showTypeMapWithLMSChar("cabbage")
   cabbage_buckets = findBucketSizes(b"cabbage")
   cabbage_types = buildTypeMap(b"cabbage")
   #print cabbage_buckets
   #print cabbage_types
   cabbage_guess = guessLMSSort(b"cabbage", cabbage_buckets, cabbage_types)
   induceSortL(b"cabbage", cabbage_guess, cabbage_buckets, cabbage_types)
   showSuffixArray(naivelyMakeSuffixArray(b"cabbage"))
   