print('Welcome to the \"Great Casino\"')
print('In our casino you may choose to place bets on either a single number, various groupings of numbers whether the numbers are 1-36 or on zero.')
print('We know that in casual casion player can\'t have a winning strategy, however if you try to win in our casino 1000 times a row, we will give you flag.')
print('Our casino smm specialist thinks than winning is the situation, in which your balance is more than zero. \n')
print('If you will have that balance, you should type \'Gotcha\', and your score will increased by 1')
print('at start your balance at 0, but we will give you credit up to ', 2**10,', so you may place bets even if you have an not positive balance.' )
balance = 0
gotcha = 0
import random
try:
	while True:
		print('Your balance is {0}, your gotchas rate is {1}'.format(balance,gotcha))
		if balance + 2**10< 0 :
			print('You lose, you account is overdrawn')
			quit()
		print('Type 1 to place bets.\nType 2 to quit.\nType flag to achieve flag.\nType Gotcha to Gotcha. It is obvious, isn\'t it?')
		choice = input()
		if choice == '1':
			print('Type ouch to go back.\nType a group of positive numbers or a zero to place bets, divided by spaces. Count of you numbers should be divisor of 36.')
			choice = input()
			if choice == 'ouch':
				continue
			else:
				print('Type value of bet')
				bet = int(input())
				if not type(bet) is int:
					print('bet should be an integer')
					continue
				elif  2**10 < bet - balance:
					print('your balance can\'t be less than ', 2**10,'.')
					continue 
				choice = [int (i) for i in choice.split()]

				for i in choice:
					if not type(i) is int:
						print('sorry, only ints or ouchs')
						continue
					if i == '0' and len(choise)>0:
						print('zero must be alone')
						continue
				if len(set(choice)) != len(choice):
					print('you should use only original numbers')
					continue
				if 36 % len(choice)!= 0:
					print('Only 36 divisors')
					continue
				if 36 % len(choice) == 0:
					intg = random.randint(0,36)
					print('The winning number is ' , intg)
#					print(choice)
					if intg in choice:

						print('Congratulations. You win')
						balance += bet*(36//(len(choice)) - 1)
					else:
						print('You lose')
						balance -= bet
		elif choice == '2':
			print('bye')
			quit()
		elif choice == 'Gotcha':
			if balance>0:
				gotcha +=1
				print('commited')
				balance = 0
			else:
				print('balance < 0')
		elif choice == 'flag':
			if gotcha>=1000:
				print('paseca{m4rt1ng4l3_1s_4_w1nn1n6_str4t36y}')
			else:
				print('not now')
		
except Exception as e:
	print(e)						
	print("You are doing something wrong, try again") 
	quit()
