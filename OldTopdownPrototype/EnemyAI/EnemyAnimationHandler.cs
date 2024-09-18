using System.Collections;
using System.Collections.Generic;
using UnityEngine;

[RequireComponent(typeof(Animator))]
public class EnemyAnimationHandler : MonoBehaviour
{
    [SerializeField] private LineOfSight _lineOfSight;

    private const string _velocity = "Velocity";
    private const string _isAttacking = "isAttacking";

    private Animator _animator;

    private void Awake()
    {
        _animator = GetComponent<Animator>();
    }
    void Update()
    {
        if (_lineOfSight.GetBasicEnemyAI().GetCurrentState() == BasicEnemyAIStates.Follow ||
            _lineOfSight.GetBasicEnemyAI().GetCurrentState() == BasicEnemyAIStates.Idle)
        {
            _animator.SetFloat(_velocity, _lineOfSight._currentSpeed);
        }

        if (_lineOfSight.GetBasicEnemyAI().GetCurrentState() == BasicEnemyAIStates.Attack && PlayerStateMachine.Instance.GetCurrentState() != PlayerStates.Death)
        {
            _animator.SetBool(_isAttacking, true);
        }
        else
        {
            _animator.SetBool(_isAttacking, false);
        }
    }
}
