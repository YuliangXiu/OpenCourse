# multiAgents.py
# --------------
# Licensing Information:  You are free to use or extend these projects for
# educational purposes provided that (1) you do not distribute or publish
# solutions, (2) you retain this notice, and (3) you provide clear
# attribution to UC Berkeley, including a link to http://ai.berkeley.edu.
# 
# Attribution Information: The Pacman AI projects were developed at UC Berkeley.
# The core projects and autograders were primarily created by John DeNero
# (denero@cs.berkeley.edu) and Dan Klein (klein@cs.berkeley.edu).
# Student side autograding was added by Brad Miller, Nick Hay, and
# Pieter Abbeel (pabbeel@cs.berkeley.edu).


from util import manhattanDistance
from game import Directions
import random, util

from game import Agent



class ReflexAgent(Agent):
    """
      A reflex agent chooses an action at each choice point by examining
      its alternatives via a state evaluation function.

      The code below is provided as a guide.  You are welcome to change
      it in any way you see fit, so long as you don't touch our method
      headers.
    """


    def getAction(self, gameState):
        """
        You do not need to change this method, but you're welcome to.

        getAction chooses among the best options according to the evaluation function.

        Just like in the previous project, getAction takes a GameState and returns
        some Directions.X for some X in the set {North, South, West, East, Stop}
        """
        # Collect legal moves and successor states
        legalMoves = gameState.getLegalActions()

        # Choose one of the best actions
        scores = [self.evaluationFunction(gameState, action) for action in legalMoves]
        bestScore = max(scores)
        bestIndices = [index for index in range(len(scores)) if scores[index] == bestScore]
        chosenIndex = random.choice(bestIndices) # Pick randomly among the best

        "Add more of your code here if you want to"

        return legalMoves[chosenIndex]

    def evaluationFunction(self, currentGameState, action):
        """
        Design a better evaluation function here.

        The evaluation function takes in the current and proposed successor
        GameStates (pacman.py) and returns a number, where higher numbers are better.

        The code below extracts some useful information from the state, like the
        remaining food (newFood) and Pacman position after moving (newPos).
        newScaredTimes holds the number of moves that each ghost will remain
        scared because of Pacman having eaten a power pellet.

        Print out these variables to see what you're getting, then combine them
        to create a masterful evaluation function.
        """
        # Useful information you can extract from a GameState (pacman.py)
        successorGameState = currentGameState.generatePacmanSuccessor(action)
        newPos = successorGameState.getPacmanPosition()
        newFood = successorGameState.getFood()
        newGhostStates = successorGameState.getGhostStates()
        newScaredTimes = [ghostState.scaredTimer for ghostState in newGhostStates]

        all_food_dis = [float(util.manhattanDistance(newPos,food_pos)) for food_pos in newFood.asList()]
        all_ghost_dis = [float(util.manhattanDistance(newPos,ghost.getPosition())) for ghost in newGhostStates]

        ave_ghost_dis = float(sum(all_ghost_dis))/float(len(newGhostStates))
        ave_ghost_scare = float(sum(newScaredTimes))/float(len(newGhostStates))

        farest_dis = float(newFood.width + newFood.height)
        total_food = newFood.height * newFood.width

        if len(all_food_dis):
          ave_food_dis = float(sum(all_food_dis))/float(len(all_food_dis))
          food_score = 5/float(min(all_food_dis)) + 2/float(ave_food_dis) + 10*(total_food-float(len(all_food_dis)))
        else:
          ave_food_dis = float('inf')
          food_score = float('inf')

        ghost_dis_score = (float(min(all_ghost_dis)) + float(ave_ghost_dis))/farest_dis
        ghost_scare_score = ave_ghost_scare

        if min(all_ghost_dis) < 6 and ghost_scare_score <10:
          return 10*food_score + 200*ghost_dis_score + 5*ghost_scare_score
        else:
          return 10*food_score + 5*ghost_scare_score + ghost_dis_score

def scoreEvaluationFunction(currentGameState):
    """
      This default evaluation function just returns the score of the state.
      The score is the same one displayed in the Pacman GUI.

      This evaluation function is meant for use with adversarial search agents
      (not reflex agents).
    """
    return currentGameState.getScore()

class MultiAgentSearchAgent(Agent):
    """
      This class provides some common elements to all of your
      multi-agent searchers.  Any methods defined here will be available
      to the MinimaxPacmanAgent, AlphaBetaPacmanAgent & ExpectimaxPacmanAgent.

      You *do not* need to make any changes here, but you can if you want to
      add functionality to all your adversarial search agents.  Please do not
      remove anything, however.

      Note: this is an abstract class: one that should not be instantiated.  It's
      only partially specified, and designed to be extended.  Agent (game.py)
      is another abstract class.
    """

    def __init__(self, evalFn = 'scoreEvaluationFunction', depth = '2'):
        self.index = 0 # Pacman is always agent index 0
        self.evaluationFunction = util.lookup(evalFn, globals())
        self.depth = int(depth)

class MinimaxAgent(MultiAgentSearchAgent):
    """
      Your minimax agent (question 2)
    """

    def value(self, gameState, depth):
      if gameState.isLose() \
          or gameState.isWin() \
          or depth == self.depth*gameState.getNumAgents():
        return (None, self.evaluationFunction(gameState))
      if depth % gameState.getNumAgents() >= 1:
        return self.minValue(gameState, depth)
      else:
        return self.maxValue(gameState, depth)
    
    def maxValue(self, gameState, depth):
      agent = depth % gameState.getNumAgents()
      actions = gameState.getLegalActions(agent)
      if len(actions) == 0:
        return (None, self.evaluationFunction(gameState))
      bestValue = float('-inf')
      bestAction = None
      for action in actions:
        nextState = gameState.generateSuccessor(agent,action)
        (_,nextValue) = self.value(nextState,depth+1)
        if nextValue > bestValue:
          bestValue = nextValue
          bestAction = action        
      return (bestAction,bestValue)

    def minValue(self, gameState, depth):
      agent = depth % gameState.getNumAgents()
      actions = gameState.getLegalActions(agent)
      if len(actions) == 0:
        return (None, self.evaluationFunction(gameState))
      bestValue = float('inf')
      bestAction = None
      for action in actions:
        nextState = gameState.generateSuccessor(agent,action)
        (_,nextValue) = self.value(nextState,depth+1)
        if nextValue < bestValue:
          bestValue = nextValue
          bestAction = action        
      return (bestAction,bestValue)


    def getAction(self, gameState):
        """
          Returns the minimax action from the current gameState using self.depth
          and self.evaluationFunction.

          Here are some method calls that might be useful when implementing minimax.

          gameState.getLegalActions(agentIndex):
            Returns a list of legal actions for an agent
            agentIndex=0 means Pacman, ghosts are >= 1

          gameState.generateSuccessor(agentIndex, action):
            Returns the successor game state after an agent takes an action

          gameState.getNumAgents():
            Returns the total number of agents in the game

          gameState.isWin():
            Returns whether or not the game state is a winning state

          gameState.isLose():
            Returns whether or not the game state is a losing state
        """
        (action,value) = self.value(gameState,0)
        return action


class AlphaBetaAgent(MultiAgentSearchAgent):
    """
      Your minimax agent with alpha-beta pruning (question 3)
    """
    def value(self, gameState, alpha, beta, depth):
      if gameState.isLose() \
          or gameState.isWin() \
          or depth == self.depth*gameState.getNumAgents():
        return (None, self.evaluationFunction(gameState))
      if depth % gameState.getNumAgents() >= 1:
        return self.minValue(gameState, alpha, beta, depth)
      else:
        return self.maxValue(gameState, alpha, beta, depth)
    
    def maxValue(self, gameState, alpha, beta, depth):
      agent = depth % gameState.getNumAgents()
      actions = gameState.getLegalActions(agent)
      if len(actions) == 0:
        return (None, self.evaluationFunction(gameState))
      bestValue = float('-inf')
      bestAction = None
      for action in actions:
        nextState = gameState.generateSuccessor(agent,action)
        (_,nextValue) = self.value(nextState, alpha, beta, depth+1)
        if nextValue > bestValue:
          bestValue = nextValue
          bestAction = action
          if bestValue > beta:
            return (bestAction, bestValue)
          else:
            alpha = max(bestValue, alpha)        
      return (bestAction,bestValue)

    def minValue(self, gameState, alpha, beta, depth):
      agent = depth % gameState.getNumAgents()
      actions = gameState.getLegalActions(agent)
      if len(actions) == 0:
        return (None, self.evaluationFunction(gameState))
      bestValue = float('inf')
      bestAction = None
      for action in actions:
        nextState = gameState.generateSuccessor(agent,action)
        (_,nextValue) = self.value(nextState, alpha, beta, depth+1)
        if nextValue < bestValue:
          bestValue = nextValue
          bestAction = action
          if bestValue < alpha:
            return (bestAction, bestValue)
          else:
            beta = min(bestValue, beta)          
      return (bestAction,bestValue)

    def getAction(self, gameState):
        """
          Returns the minimax action using self.depth and self.evaluationFunction
        """
        (action,value) = self.value(gameState, float('-inf'), float('inf'),0)
        return action
       

class ExpectimaxAgent(MultiAgentSearchAgent):
    """
      Your expectimax agent (question 4)
    """
    def value(self, gameState, depth):
      if gameState.isLose() \
          or gameState.isWin() \
          or depth == self.depth*gameState.getNumAgents():
        return (None, self.evaluationFunction(gameState))
      if depth % gameState.getNumAgents() >= 1:
        return self.expectValue(gameState, depth)
      else:
        return self.maxValue(gameState, depth)
    
    def maxValue(self, gameState, depth):
      agent = depth % gameState.getNumAgents()
      actions = gameState.getLegalActions(agent)
      if len(actions) == 0:
        return (None, self.evaluationFunction(gameState))
      bestValue = float('-inf')
      bestAction = None
      for action in actions:
        nextState = gameState.generateSuccessor(agent,action)
        (_,nextValue) = self.value(nextState, depth+1)
        if nextValue > bestValue:
          bestValue = nextValue
          bestAction = action
      return (bestAction,bestValue)

    def expectValue(self, gameState, depth):
      agent = depth % gameState.getNumAgents()
      actions = gameState.getLegalActions(agent)
      if len(actions) == 0:
        return (None, self.evaluationFunction(gameState))
      expectValue = 0
      for action in actions:
        nextState = gameState.generateSuccessor(agent,action)
        (_,nextValue) = self.value(nextState, depth+1)
        expectValue += nextValue
      return (None,float(expectValue)/len(actions))

    def getAction(self, gameState):
        """
          Returns the expectimax action using self.depth and self.evaluationFunction

          All ghosts should be modeled as choosing uniformly at random from their
          legal moves.
        """
        (action,value) = self.value(gameState,0)
        return action
       

def betterEvaluationFunction(currentGameState):
    """
      Your extreme ghost-hunting, pellet-nabbing, food-gobbling, unstoppable
      evaluation function (question 5).

      DESCRIPTION: <write something here so we know what you did>
    """
    newPos = currentGameState.getPacmanPosition()
    newFood = currentGameState.getFood()
    newGhostStates = currentGameState.getGhostStates()
    newScaredTimes = [ghostState.scaredTimer for ghostState in newGhostStates]

    all_food_dis = [float(util.manhattanDistance(newPos,food_pos)) for food_pos in newFood.asList()]
    all_ghost_dis = [float(util.manhattanDistance(newPos,ghost.getPosition())) for ghost in newGhostStates]

    ave_ghost_dis = float(sum(all_ghost_dis))/float(len(newGhostStates))
    ave_ghost_scare = float(sum(newScaredTimes))/float(len(newGhostStates))

    farest_dis = float(newFood.width + newFood.height)
    total_food = newFood.height * newFood.width

    if len(all_food_dis):
      ave_food_dis = float(sum(all_food_dis))/float(len(all_food_dis))
      food_score = 5/float(min(all_food_dis)) + 2/float(ave_food_dis) + 10*(total_food-float(len(all_food_dis)))
    else:
      ave_food_dis = float('inf')
      food_score = float('inf')

    ghost_dis_score = (float(min(all_ghost_dis)) + float(ave_ghost_dis))/farest_dis
    ghost_scare_score = ave_ghost_scare

    if min(all_ghost_dis) < 8 and ghost_scare_score <14:
      return 10*food_score + 440*ghost_dis_score + 10*ghost_scare_score
    else:
      return 10*food_score + 10*ghost_scare_score + 50*ghost_dis_score


    

# Abbreviation
better = betterEvaluationFunction

