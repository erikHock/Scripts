using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System;

[RequireComponent(typeof(PlayerMovement))]
public class PlayerAnimationHandler : MonoBehaviour
{
    [SerializeField] Animator _animator;

    private const string _isRunning = "isRunning";
    private const string _interact = "Interact";
    private const string _death = "Death";

    public static Action OnAnimationComplete;

    private void OnEnable()
    {
        PlayerMovement.OnPlayerMove += OnMove;
        PlayerStateMachine.Instance.OnStateChange += OnInteract;
        PlayerStateMachine.Instance.OnStateChange += OnDeath;
    }

    private void OnDisable()
    {
        PlayerMovement.OnPlayerMove -= OnMove;
        PlayerStateMachine.Instance.OnStateChange -= OnInteract;
        PlayerStateMachine.Instance.OnStateChange -= OnDeath;
    }

    private void OnInteract(PlayerStates state)
    {
        if (state == PlayerStates.Interact)
        {
            _animator.SetTrigger(_interact);
        }
    }

    private void OnMove(bool b)
    {
        _animator.SetBool(_isRunning, b);
    }

    private void OnDeath(PlayerStates state)
    {
        if (state == PlayerStates.Death)
        {
            _animator.SetTrigger(_death);
        }
    }
}
