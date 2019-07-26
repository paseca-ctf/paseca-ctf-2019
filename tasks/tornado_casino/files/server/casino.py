from sys import argv
from random import getrandbits

flag = 'paseca{d1d_y0u_r34lly_7h1nk_7h47_7h3_m41n_1nc0m3_0f_b335_15_h0n3y?}'

tornado_banner = '''
                                                              88              
  ,d                                                          88              
  88                                                          88              
MM88MMM ,adPPYba,  8b,dPPYba, 8b,dPPYba,  ,adPPYYba,  ,adPPYb,88  ,adPPYba,   
  88   a8"     "8a 88P'   "Y8 88P'   `"8a ""     `Y8 a8"    `Y88 a8"     "8a  
  88   8b       d8 88         88       88 ,adPPPPP88 8b       88 8b       d8  
  88,  "8a,   ,a8" 88         88       88 88,    ,88 "8a,   ,d88 "8a,   ,a8"  
  "Y888 `"YbbdP"'  88         88       88 `"8bbdP"Y8  `"8bbdP"Y8  `"YbbdP"' '''
casino_banner = '''
                                88                          
                                ""                          
                                                            
 ,adPPYba, ,adPPYYba, ,adPPYba, 88 8b,dPPYba,   ,adPPYba,   
a8"     "" ""     `Y8 I8[    "" 88 88P\'   `"8a a8"     "8a  
8b         ,adPPPPP88  `"Y8ba,  88 88       88 8b       d8  
"8a,   ,aa 88,    ,88 aa    ]8I 88 88       88 "8a,   ,a8"  
 `"Ybbd8"' `"8bbdP"Y8 `"YbbdP"\' 88 88       88  `"YbbdP"\' '''
tornado_art = '''

   ((  "####@@!!$$    ))
       `#####@@!$$`  ))
    ((  '####@!!$:
   ((  ,####@!!$:   ))
       .###@!!$:
       `##@@!$:
        `#@!!$
  !@#    `#@!$:       @#$
   #$     `#@!$:       !@!
            '@!$:
        '`\   "!$: /`'
           '\  '!: /'
             "\ : /"
  -."-/\\\-."//.-"/:`\."-.JrS"."-=_\\
" -."-.\\"-."//.-".`-."_\\-.".-\".-//'''


welcome = 'Welcome!\n[1] - To slotmachine\n[2] - Enter promocode\n[3] - Exit\n'''
def sltmchn_wndw(num):
    return '|' + '|'.join(list(hex(num)[2:].zfill(8))) + '|'
slotmachine_menu = '[$] - $$$SPIN$$$\n'


print(tornado_banner)
print(casino_banner)
print(tornado_art)
user_balance = 10#$
promo = ''
while True:
    choice1 = input(welcome)
    if choice1 == '1':
        print('$$$Its point of no return!$$$\n$$$     all or nothing    $$$\n')
        print(f'Your balance: {user_balance}')
        while True:
            if user_balance > 0:
                spin = input(slotmachine_menu)
                if spin == '$':
                    state = getrandbits(32)
                    try:
                        pff_try = int(input('It will be: '), 16)
                    except:
                        exit(0)
                    if pff_try == state:
                        print(sltmchn_wndw(state))
                        print('OMGWTF$$$$$$$$$$$$')
                        print(flag)
                        exit(0)
                    else:
                        print(sltmchn_wndw(state))
                        print('Nice try!')
                        user_balance -= 1
                        print(f'Your balance: {user_balance}')
                else:
                    exit(0)
            else:
                print('Sorry!')
                exit(0)
                    
    elif choice1 == '2':
        if not promo:
            promo = input('Enter your promocode: ')
            if promo == 'b33_1_4m_b3333':
                print('Great!')
                user_balance += 1000#$
        else:
            print('Only once!')
            
    elif choice1 == '3':
        exit(0)




