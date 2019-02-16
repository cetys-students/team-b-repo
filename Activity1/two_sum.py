# Given an array of integers, return indices of the two numbers such that they add up to a specific target.
# You may assume that each input would have exactly one solution, and you may not use the same element twice.
#
# Example:
#
# Given nums = [2, 7, 11, 15], target = 9,
#
# Because nums[0] + nums[1] = 2 + 7 = 9,
# return [0, 1].

class Solution:
    def twoSum(self, nums: 'List[int]', target: 'int') -> 'List[int]':
        datos = {} #crea diccionarios
        for i, num in enumerate(nums): #cuenta posiciones
            dif = target - num #resta
            if datos.get(num) is None: #tomar un NUM de NUMS
                datos[dif] = i
            else:
                return [datos[num], i]

solution = Solution().twoSum([2, 11, 7, 15], 9)
print(solution)
