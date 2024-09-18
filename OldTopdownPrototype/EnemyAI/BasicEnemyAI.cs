using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System;


public class BasicEnemyAI : MonoBehaviour
{
    private BasicEnemyAIStates _currentState;

    public static event Action<BasicEnemyAIStates> OnEnemyAiChangeState;
    
    public void ChangeEnemyAIState(BasicEnemyAIStates state)
    {
        _currentState = state;

        switch (state)
        {
            case BasicEnemyAIStates.Idle:
                break;
            case BasicEnemyAIStates.Follow: 
                break;
            case BasicEnemyAIStates.Attack: 
                break;
            case BasicEnemyAIStates.Death: 
                GetComponentInChildren<RagdollHandler>().TriggerRagdoll();
                GetComponentInChildren<Canvas>().enabled = false;
                break;
        }

        OnEnemyAiChangeState?.Invoke(state);
    }

    public BasicEnemyAIStates GetCurrentState()
    {
        return _currentState;
    }
}

public enum BasicEnemyAIStates
{
    Idle,
    Follow,
    Attack,
    Death
}
