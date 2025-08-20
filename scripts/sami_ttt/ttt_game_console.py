#!/usr/bin/env python3

# ttt_game_console.py
#
# Kyle Vickstrom
#
# This is the console controller of SAMI's tic tac toe game.
# This is used to test individual nodes and can manually run the game through those mechanisms.
# 
# based on the trivia controller,
# Uses curses to draw a custom shell like interface

import rclpy
from rclpy.node import Node
from rclpy.action import ActionClient
from rclpy.time import Time
import curses

from sami_ttt_msgs.msg import GameLog, GameState
from sami_ttt_msgs.srv import NewGame, PlayerTurn
from sami_ttt_msgs.srv import MistyConnect
from sami_ttt_msgs.action import MistyMovement
#from sami_trivia_msgs.srv import NewQuestion, SerialConnect, CheckAnswer
#from sami_trivia_msgs.action import MoveSami, Speak, Listen

class TicTacConsole(Node):
    def __init__(self):
        super().__init__('ttt_console')
        self.started = False
        self.moving = False
        self.connected = False
        self.inputMode = False
        self.gameLog = []
        self.score = None
        self.pubLog = self.create_publisher(GameLog, 'game_log', 10)
        self.subLog = self.create_subscription(GameLog, 'game_log', self.logsubscriber, 10)
        self.subGame = self.create_subscription(GameState, 'game_state', self.readGameState, 10)
        self.newGame_client = self.create_client(NewGame, 'new_game')
        self.newTurn_client = self.create_client(PlayerTurn, 'player_turn')
        self.connect_client = self.create_client(MistyConnect, 'misty_connect')

        self.mistyMove_client = ActionClient(self, MistyMovement, "mistymovement")

        # self.moveClient = ActionClient(self, MoveSami, 'move_sami')
        # self.arduinoClient = self.create_client(SerialConnect, 'serial_connect')

    def startConsole(self, stdscr):
        """
        This is the main loop
            though other functions can take control with their own loop, like the user cmd input
        """
        curses.cbreak()
        curses.start_color()
        curses.use_default_colors()
        curses.init_pair(1, curses.COLOR_GREEN,-1)
        curses.init_pair(2, curses.COLOR_RED,-1)
        stdscr.keypad(True)
        stdscr.nodelay(True)
        stdscr.refresh()
        self.log("Press SPACE to start...")
        #print("Press SPACE to start...")
        while rclpy.ok():
            rclpy.spin_once(self, timeout_sec=0.1)

            # write to terminal screen
            stdscr.clear()
            height, width = stdscr.getmaxyx()
            usable_height = height - 4 - 4      # 1 title, 1 divider, 2 keybinds, 4 user cmd input

            self.drawScreen(stdscr, height, width, usable_height)
            

            # key keybind inputs
            key = stdscr.getch()
           
            if key != -1:
                if key == 32: # space key
                    if not self.started:
                        self.started = True
                        self.log("Starting game...")
                        self.newGame_request()
                    #self.get_logger().info("Starting game...")
                
                elif key == 10: # enter key
                    self.log("enter key")

                elif key == ord('c'):
                    # save port, baudrate to class instance var
                    port = self.drawInputMode(stdscr, height, width, usable_height, mode="connect_port")
                    baudrate = self.drawInputMode(stdscr, height, width, usable_height, mode="connect_baud")
                    # self.connectSAMI()
                    
                elif key == ord('i'):
                    # input mode
                    self.log("Entering Input mode")
                    self.inputMode = True
                    user_input = self.drawInputMode(stdscr, height, width, usable_height)
                    self.inputMode = False
                    self.handleUserCMD(user_input)

                elif key == ord('q'):
                    self.log("Exiting...")
                    break
            
            stdscr.refresh()

        # outside loop, quitting
        stdscr.clear()
    
    def drawScreen(self, stdscr, height, width, usable_height):
        """
        Draws the log and keybinds to curses terminal
        """
        stdscr.addstr(0, 0, "Log:")
        # draw log
        logs_to_show = self.gameLog[-usable_height:] if usable_height > 0 else []
        for i, msg in enumerate(logs_to_show):
            stamp = Time.from_msg(msg.stamp).to_msg()
            time_str = f"{stamp.sec % 86400//3600:02}:{stamp.sec%3600//60:02}:{stamp.sec%60:02}"
            line = f"[{time_str}][{msg.node_name}] {msg.content}"
            stdscr.addstr(i+1, 2, f"> {line[:width-4]}")

        # draw keybinds
        stdscr.addstr(height-3, 0, "-"*(width-1))
        #stdscr.addstr(height-2,0,"Keybinds: [Q] QUIT [C] Connect SAMI [ENTER] New Question")
        key_str = "Keybinds: "
        q_str = "[Q] QUIT "
        c_str = "[C] Connect Misty "
        i_str = "[I] Input Mode "
        '''
        if self.waiting:
            enter_str = "[ENTER] New Question "
        else:
            enter_str = "[ENTER] Answer Question "
        '''

        stdscr.addstr(height-2, 0, key_str)
        stdscr.addstr(height-2, len(key_str), q_str)
        '''
        if not self.arduinoConnected:
            stdscr.addstr(height-2,len(key_str)+len(q_str), c_str, curses.color_pair(2))
        else:
        '''
        stdscr.addstr(height-2,len(key_str)+len(q_str), c_str, curses.color_pair(1))
        if not self.inputMode:
            stdscr.addstr(height-2,len(key_str)+len(q_str)+len(c_str), i_str)
        else:
            stdscr.addstr(height-2,len(key_str)+len(q_str)+len(c_str), i_str, curses.color_pair(1))

        # stdscr.addstr(height-2,len(key_str)+len(q_str)+len(c_str)+len(i_str), enter_str)
        

    def drawInputMode(self, stdscr, height, width, usable_height, mode="cmd"):
        """
        Handles user cmd input mode. 
        reuturns the input for another function to handle, kind of like mini shell
        """
        input_y = height-4
        input_x = 6
        stdscr.addstr(input_y, 0, "CMD >")
        if mode == "cmd":
            stdscr.addstr(input_y - 1, 0, "INPUT MODE: ESC TO LEAVE", curses.color_pair(1))
        '''
        elif mode == "connect_port":
            stdscr.addstr(input_y - 1, 0, f"CONFIRM OR ENTER NEW PORT: {self.arduinoPort}", curses.color_pair(1))
        elif mode == "connect_baud":
            stdscr.addstr(input_y - 1, 0, f"CONFIRM OR ENTER NEW BAUDRATE: {self.arduinoBaudrate}", curses.color_pair(1))
        '''
        #curses.echo()
        #stdscr.nodelay(False) # enter blocking mode
        user_input = ""
        #stdscr.move(input_y, input_x)
        while rclpy.ok():
            rclpy.spin_once(self, timeout_sec=0.1)
            self.drawScreen(stdscr, height, width, usable_height)
            stdscr.move(input_y, input_x)
            stdscr.clrtoeol()
            stdscr.addstr(input_y, input_x, user_input)
            #stdscr.move(input_y, input_x+len(user_input))
            stdscr.refresh()
            ch = stdscr.getch()

            # ESC to cancel
            if ch == 27:
                self.log("Leaving Input mode")
                user_input = None
                break
            # Enter cmd
            elif ch in (curses.KEY_ENTER, 10, 13):
                break
            # backspace
            elif ch in (curses.KEY_BACKSPACE, 127):
                if len(user_input) > 0:
                    user_input = user_input[:-1]
                    #stdscr.delch(input_y, input_x+len(user_input))
                    #stdscr.move(input_y, input_x+len(user_input))
            else:
                # add to user input string
                try:
                    char = chr(ch)
                    user_input += char
                    #stdscr.addstr(input_y, input_x+len(user_input), user_input)
                    #stdscr.move(input_y, input_x+len(user_input))
                except ValueError:
                    continue # ignore weird chars that dont print
        
        self.log(f"[USER INPUT] {user_input}")
        return user_input

    def handleUserCMD(self, user_input):
        """
        Logic to handle input commands
        Available commands
            move <filename.json>        this calls the action client with the filename to move sami
            connect <port> <baudrate>   this connects to the arduino
        """
        if user_input is None:
            #self.log("[USER INPUT] : [NONE]")
            return
        tokens = user_input.strip().split()
        if not tokens:
            self.log("[USER INPUT] : [NONE]")
            return

        cmd = tokens[0]
        args = tokens[1:]

        self.log(f"[CMD]: {cmd}  [ARGS]: {args}")

        if cmd == "move":
            self.log("no more sami to move, TODO: implement misty moving?")
            
        elif cmd == "connect":
            self.log('connect no work rn')

        elif cmd == "turn":
            if len(args) != 2:
                self.log("USAGE: turn <player_id> <location>")
                return
            try:
                player_id = int(args[0])
                loc = int(args[1])
            except ValueError:
                self.log("player_id and location must be int")
                return
            self.newTurn_request(player_id, loc)

        elif cmd == "newgame":
            self.newGame_request()


        else:
            self.log("[USER INPUT] theres not anything implemented here yet")
            return
        return

    def newGame_request(self):
        """
        Service request to game node to create a new game.
        """
        if not self.newGame_client.wait_for_service(timeout_sec=1):
            self.log("Game node not active.")
            return
        request = NewGame.Request()
        self.NewGame_response = self.newGame_client.call_async(request)
        self.log("Requested new game")

    def newTurn_request(self, player_id:int, location: int):
        """
        Service request to make a turn
        id 0 = cpu, 1 = human
        """
        if not self.newTurn_client.wait_for_service(timeout_sec=1):
            self.log("Game node not active")
            return

        newTurn = PlayerTurn.Request()
        newTurn.player_id = player_id
        newTurn.location = location
        self.newTurn_response = self.newTurn_client.call_async(newTurn)
        self.log(f"Requested turn for id {player_id}, location {location}")

    def mistyConnect_request(self):
        """
        Service request to connect to misty robot
        """
        if not self.connect_client.wait_for_service(timeout_sec=1):
            self.log("misty node not active")
            return

        self.connected = True

        newMisty = MistyConnect.Request()
        newMisty.ip = "192.168.0.174"
        self.newMisty_response = self.connect_client.call_async(newMisty)
        self.log("Requested to connect to misty")

    def moveMisty(self, emote):
        """
        Action call to animate misty
        """
        if self.moving:
            self.log("misty currently moving!")
            return
        else:
            self.moving = True
        goal = MistyMovement.Goal()
        goal.behavior = emote
        self.moveClient.wait_for_server()

        self.moveResult = self.moveClient.send_goal_async(goal, feedback_callback=self.move_feedback)
        self.moveResult.add_done_callback(self.move_response)

    def move_feedback(self, msg):
        """
        Feedback callback for the movement action server
        """
        self.log(msg.progress)

    def move_response(self, future):
        """
        action accepted or rejected
        """
        self.move_goal_handle = future.result()

        if not self.move_goal_handle.accepted:
            self.log(f"misty move not accepted")
            return

        self.move_result_handle = self.move_goal_handle.get_result_async()
        self.move_result_handle.add_done_callback(self.mistyDoneMoving)

    def mistyDoneMoving(self, future):
        """
        This is called when misty has finished moving
        """
        self.moving = False




    def log(self, msg):
        """
        log to topic and to curses terminal window
        """
        newmsg = GameLog()
        newmsg.stamp = self.get_clock().now().to_msg()
        newmsg.node_name = self.get_name()
        newmsg.content = msg
        self.pubLog.publish(newmsg)

    def logsubscriber(self, msg):
        """
        Subscriber callback to the game_log. this is what edits the internal log that curses shows
        """
        if len(self.gameLog) >=50:
            self.gameLog.pop(0)
        self.gameLog.append(msg)

    def readGameState(self, msg: GameState):
        """
        Subscriber callback to the GameState topic
        """
        self.score = msg.score
        for i in range(0, 9, 3):
            row = msg.board[i:i+3]
            self.log(str(row))

def createConsole(args=None):
    rclpy.init(args=args)
    game = TicTacConsole()
    curses.wrapper(game.startConsole)
    rclpy.shutdown()

if __name__ == "__main__":
    createConsole()