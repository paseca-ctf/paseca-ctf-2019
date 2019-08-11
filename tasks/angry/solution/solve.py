# -*- coding: utf-8 -*-
# @Author: madrat
# @Date:   2019-05-03 22:43:43

import angr
import claripy

flagLen = 36
findAddr = 0x400000 + 0x185A # 0x4013EA
avoidAddr = 0x400000 + 0x1868

def main():
    proj = angr.Project('./angry', load_options={"auto_load_libs": True})
    
    argv1 = claripy.BVS("argv1", flagLen * 8)
    initial_state = proj.factory.full_init_state(args=["./angry", argv1], add_options=angr.options.unicorn)

    for byte in argv1.chop(8):
        # initial_state.add_constraints(byte != '\x00') # null
        initial_state.add_constraints(byte > ' ') # '\x20'
        initial_state.add_constraints(byte <= '~') # '\x7e'

    initial_state.add_constraints(argv1.chop(8)[0] == 'p')
    initial_state.add_constraints(argv1.chop(8)[1] == 'a')
    initial_state.add_constraints(argv1.chop(8)[2] == 's')
    initial_state.add_constraints(argv1.chop(8)[3] == 'e')
    initial_state.add_constraints(argv1.chop(8)[4] == 'c')
    initial_state.add_constraints(argv1.chop(8)[5] == 'a')
    initial_state.add_constraints(argv1.chop(8)[6] == '{')

    simulation_manager = proj.factory.simulation_manager(initial_state)
    simulation_manager.explore(find=findAddr, avoid=avoidAddr)

    try:
        found = simulation_manager.found[0]
        solution = found.solver.eval(argv1, cast_to=bytes)
        print('[+] Found flag: %s' % solution)
    except:
        print('[-] Flag not found!')

if __name__ == "__main__":
    main()