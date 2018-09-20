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
   
       summaryString, summaryAlphabetSize, summarySuffixOffsets = \
           summariseSuffixArray(string, guessedSuffixArray, typeMap)
   
       summarySuffixArray = makeSummarySuffixArray(summaryString, summaryAlphabetSize)
   
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
       #print bucketHeads
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
   
   
   def induceSortS(string, guessedSuffixArray, bucketSizes, typeMap):
       bucketTails = findBucketTails(bucketSizes)
       for i in range(len(guessedSuffixArray)-1, -1, -1):
           j = guessedSuffixArray[i] - 1
           if j < 0:
               continue
           if typeMap[j] != S_TYPE:
               continue
           bucketIndex = ord(string[j])
           guessedSuffixArray[bucketTails[bucketIndex]] = j
           bucketTails[bucketIndex] -= 1
           showSuffixArray(guessedSuffixArray, i)
   
   
   def summariseSuffixArray(string, guessedSuffixArray, typeMap):
       currentName = 0
       lastLMSSuffixOffset = None
       lmsNames = [-1] * (len(string) + 1)
       lmsNames[guessedSuffixArray[0]] = currentName
       lastLMSSuffixOffset = guessedSuffixArray[0]
       showSuffixArray(lmsNames)
   
       for i in range(1, len(guessedSuffixArray)):
           suffixOffset = guessedSuffixArray[i]
           if not isLMSChar(suffixOffset, typeMap):
               continue
           if not cmpLMSChar(string, typeMap, lastLMSSuffixOffset, suffixOffset):
               currentName += 1
           lastLMSSuffixOffset = suffixOffset
           lmsNames[suffixOffset] = currentName
           showSuffixArray(lmsNames)
   
       summaryString = []
       summarySuffixOffsets = []
       for index, name in enumerate(lmsNames):
           if name == -1:
               continue
           summaryString.append(name)
           summarySuffixOffsets.append(index)
   
       summaryAlphabetSize = currentName + 1
       return summaryString, summaryAlphabetSize, summarySuffixOffsets
   
   def makeSummarySuffixArray(summaryString, summaryAlphabetSize):
       if summaryAlphabetSize == len(summaryString):
           summarySuffixArray = [-1] * (len(summaryString) + 1)
           summarySuffixArray[0] = len(summaryString)
           for x in range(len(summaryString)):
               y = summaryString[x]
               summarySuffixArray[y+1] = x
       else:
           summarySuffixArray = makeSuffixArrayByInducedSorting(summaryString, summaryAlphabetSize)
       return summarySuffixArray
   
   
   def accurateLMSSort(string, bucketSizes, typeMap, summarySuffixArray, summarySuffixOffsets):
       suffixOffsets = [-1] * (len(string) + 1)
       bucketTails = findBucketTails(bucketSizes)
       for i in range(len(summarySuffixArray)-1, 1, -1):
           stringIndex = summarySuffixOffsets[summarySuffixArray[i]]
           bucketIndex = ord(string[stringIndex])
           suffixOffsets[bucketTails[bucketIndex]] = stringIndex
           bucketTails[bucketIndex] -= 1
           showSuffixArray(suffixOffsets)
       suffixOffsets[0] = len(string)
       showSuffixArray(suffixOffsets)
       return suffixOffsets
   
   cabbage = b"cabbage"
   cabbage_buckets = findBucketSizes(cabbage)
   cabbage_types = buildTypeMap(cabbage)
   cabbage_guess = guessLMSSort(cabbage, cabbage_buckets, cabbage_types)
   induceSortL(cabbage, cabbage_guess, cabbage_buckets, cabbage_types)
   (
       cabbage_summary, 
       cabbage_alphabet_size, 
       cabbage_summary_suffix_offsets
   ) = summariseSuffixArray(cabbage, cabbage_guess, cabbage_types)
   showTypeMapWithLMSChar(cabbage)
   print cabbage_alphabet_size
   print cabbage_summary
   print cabbage_summary_suffix_offsets
   cabbage_summary_suffix_array = makeSummarySuffixArray(cabbage_summary, cabbage_alphabet_size)
   showSuffixArray(cabbage_summary_suffix_array)
   showSuffixArray(naivelyMakeSuffixArray(cabbage_summary))
   cabbage_real = accurateLMSSort(cabbage, cabbage_buckets,
       cabbage_types, 
       cabbage_summary_suffix_array,
       cabbage_summary_suffix_offsets)
   
   showSuffixArray(makeSuffixArrayByInducedSorting(cabbage, 256))
   showSuffixArray(naivelyMakeSuffixArray(cabbage))
   
   #baa = b"baabaabac"
   #baa_types = buildTypeMap(baa)
   #baa_buckets = findBucketSizes(baa)
   #baa_guess = guessLMSSort(baa, baa_buckets, baa_types)
   #induceSortL(baa, baa_guess, baa_buckets, baa_types)
   #induceSortS(baa, baa_guess, baa_buckets, baa_types)
   #showSuffixArray(naivelyMakeSuffixArray(baa))
   #showTypeMap(baa)
   #(
   #    baa_summary,
   #    baa_alphabet_size,
   #    baa_summar_suffix_offsets
   #) = summariseSuffixArray(baa, baa_guess, baa_types)
   #showTypeMapWithLMSChar(baa)
   #print baa_summary
   #print baa_summar_suffix_offsets
   #print cabbage_alphabet_size
   