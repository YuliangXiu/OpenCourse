# search.py
# ---------
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


"""
In search.py, you will implement generic search algorithms which are called by
Pacman agents (in searchAgents.py).
"""

import util
import searchAgents
import copy

class Node:
    def __init__(self, position, path=[], cost=0, leftcorner=set()):
        self.path = path
        self.position = position
        self.cost = cost
        self.leftCorners = leftcorner
    def getPath(self):
        return self.path
    def getPosition(self):
        return self.position
    def getCost(self):
        return self.cost
    def getLeftCorners(self):
        return self.leftCorners


class SearchProblem:
    """
    This class outlines the structure of a search problem, but doesn't implement
    any of the methods (in object-oriented terminology: an abstract class).

    You do not need to change anything in this class, ever.
    """

    def getStartState(self):
        """
        Returns the start state for the search problem.
        """
        util.raiseNotDefined()

    def isGoalState(self, state):
        """
          state: Search state

        Returns True if and only if the state is a valid goal state.
        """
        util.raiseNotDefined()

    def getSuccessors(self, state):
        """
          state: Search state

        For a given state, this should return a list of triples, (successor,
        action, stepCost), where 'successor' is a successor to the current
        state, 'action' is the action required to get there, and 'stepCost' is
        the incremental cost of expanding to that successor.
        """
        util.raiseNotDefined()

    def getCostOfActions(self, actions):
        """
         actions: A list of actions to take

        This method returns the total cost of a particular sequence of actions.
        The sequence must be composed of legal moves.
        """
        util.raiseNotDefined()


def tinyMazeSearch(problem):
    """
    Returns a sequence of moves that solves tinyMaze.  For any other maze, the
    sequence of moves will be incorrect, so only use this for tinyMaze.
    """
    from game import Directions
    s = Directions.SOUTH
    w = Directions.WEST
    return  [s, s, w, s, w, w, s, w]

def depthFirstSearch(problem):
    """
    Search the deepest nodes in the search tree first.

    Your search algorithm needs to return a list of actions that reaches the
    goal. Make sure to implement a graph search algorithm.

    To get started, you might want to try some of these simple commands to
    understand the search problem that is being passed in:

    print "Start:", problem.getStartState()
    print "Is the start a goal?", problem.isGoalState(problem.getStartState())
    print "Start's successors:", problem.getSuccessors(problem.getStartState())
    """
    closed = set()
    startNode = Node(problem.getStartState())
    fringe = util.Stack()
    fringe.push(startNode)
    while not fringe.isEmpty():
        node = fringe.pop()
        if problem.isGoalState(node.getPosition()):
            return node.getPath()
        if node.getPosition() not in closed:
            closed.add(node.getPosition())
            for _ in problem.getSuccessors(node.getPosition()):
                child_path = node.getPath()[:]
                child_path.append(_[1])
                child_node = Node(_[0], child_path)
                fringe.push(child_node)

def breadthFirstSearch(problem):
    """Search the shallowest nodes in the search tree first."""
    closed = []
    if isinstance(problem, searchAgents.CornersProblem):
        startNode = Node(problem.getStartState(), leftcorner=set(problem.corners))
    else:
        startNode = Node(problem.getStartState())
    fringe = util.Queue()
    fringe.push(startNode)
    while not fringe.isEmpty():
        node = fringe.pop()
        if isinstance(problem, searchAgents.CornersProblem):
            if problem.isGoalState(node):
                return node.getPath()
            node_id = [node.getPosition(),node.getLeftCorners()]
            if node_id not in closed:
                closed.append(node_id)
                for _ in problem.getSuccessors(node.getPosition()):
                    childlc = copy.deepcopy(node.getLeftCorners())
                    if _[0] in node.getLeftCorners():
                        childlc.remove(_[0])
                    newNode = Node(_[0],node.getPath()+[_[1]],_[2],childlc)
                    # print newNode.getPath()
                    fringe.push(newNode)
                # for _ in problem.getSuccessors(node):
                #     fringe.push(_)

        else:
            if problem.isGoalState(node.getPosition()):
                return node.getPath()
            if node.getPosition() not in closed:
                closed.append(node.getPosition())
                for _ in problem.getSuccessors(node.getPosition()):
                    child_path = node.getPath()[:]
                    child_path.append(_[1])
                    child_node = Node(_[0], child_path)
                    fringe.push(child_node)

def uniformCostSearch(problem):
    """Search the node of least total cost first."""
    closed = set()
    startNode = Node(problem.getStartState())
    fringe = util.PriorityQueue()
    fringe.push(startNode,startNode.getCost())
    while not fringe.isEmpty():
        node = fringe.pop()
        if problem.isGoalState(node.getPosition()):
            return node.getPath()
        if node.getPosition() not in closed:
            closed.add(node.getPosition())
            for _ in problem.getSuccessors(node.getPosition()):
                child_path = node.getPath()[:]
                child_path.append(_[1])
                child_node = Node(_[0], child_path)
                child_node.cost = node.getCost()+_[2]
                fringe.push(child_node,child_node.getCost())

def nullHeuristic(state, problem=None):
    """
    A heuristic function estimates the cost from the current state to the nearest
    goal in the provided SearchProblem.  This heuristic is trivial.
    """
    return 0

def aStarSearch(problem, heuristic=nullHeuristic):
    """Search the node that has the lowest combined cost and heuristic first."""
    closed = []
    fringe = util.PriorityQueue()
    if isinstance(problem, searchAgents.CornersProblem):
        startNode = Node(problem.getStartState(), leftcorner=set(problem.corners))
        fringe.push(startNode, startNode.getCost()+heuristic(startNode,problem))
    else:
        startNode = Node(problem.getStartState())
        fringe.push(startNode, startNode.getCost()+heuristic(startNode.getPosition(),problem))
   

    while not fringe.isEmpty():
        node = fringe.pop()
        if isinstance(problem, searchAgents.CornersProblem):
            if problem.isGoalState(node):
                return node.getPath()
            node_id = [node.getPosition(),node.getLeftCorners()]
            if node_id not in closed:
                closed.append(node_id)
                for _ in problem.getSuccessors(node.getPosition()):
                    childlc = copy.deepcopy(node.getLeftCorners())
                    if _[0] in node.getLeftCorners():
                        childlc.remove(_[0])
                    newNode = Node(_[0],node.getPath()+[_[1]],_[2],childlc)
                    fringe.push(newNode,_[2]+heuristic(newNode,problem))
        else:
            if problem.isGoalState(node.getPosition()):
                return node.getPath()
            if node.getPosition() not in closed:
                closed.append(node.getPosition())
                for _ in problem.getSuccessors(node.getPosition()):
                    child_path = node.getPath()[:]
                    child_path.append(_[1])
                    child_node = Node(_[0], child_path)
                    child_node.cost = node.cost+_[2]
                    fringe.push(child_node, child_node.getCost()+heuristic(child_node.getPosition(),problem))


# Abbreviations
bfs = breadthFirstSearch
dfs = depthFirstSearch
astar = aStarSearch
ucs = uniformCostSearch
