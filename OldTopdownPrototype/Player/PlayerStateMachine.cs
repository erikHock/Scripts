using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System;
using UnityEngine.Animations.Rigging;

public class PlayerStateMachine : MonoBehaviour
{
    public static PlayerStateMachine Instance;
    public Action<PlayerStates> OnStateChange;
    public Action OnInteractEnd;

    [SerializeField]private PlayerStates _previusState;
    [SerializeField]private PlayerStates _currentState;

    private void Awake()
    {
        Instance = this;

    }

    private void Start()
    {
        ChangePlayerState(PlayerStates.Attack);
    }

    public void ChangePlayerState(PlayerStates state)
    {
        _previusState = _currentState;
        _currentState = state;

        switch (state)
        {
            case PlayerStates.Interact:
                GameManager.Instance.ChangeGameState(GameStates.GamePaused);
                break;

            case PlayerStates.Attack:
                GameManager.Instance.ChangeGameState(GameStates.GameLoop);
                break;

            case PlayerStates.Death:
                Rigidbody rb = GetComponent<Rigidbody>();
                Physics.IgnoreLayerCollision(LayerMask.NameToLayer("Player"), LayerMask.NameToLayer("Enemy"));
                rb.isKinematic = false;
                rb.useGravity = true;
                
                GetComponentInChildren<Rig>().weight = 0;
                GetComponentInChildren<WeaponHandler>().gameObject.SetActive(false);
                GetComponentInChildren<RagdollHandler>().TriggerRagdoll();
                
                GameManager.Instance.ChangeGameState(GameStates.GameEnd);
                break;
        }

        OnStateChange?.Invoke(state);

        if (state != PlayerStates.Interact && PlayerStateMachine.Instance.GetPreviousState() == PlayerStates.Interact)
        {
            OnInteractEnd?.Invoke();
            _previusState = PlayerStates.Attack;
        }
    }

    public PlayerStates GetCurrentState()
    {
        return _currentState;
    }

    public PlayerStates GetPreviousState()
    {
        return _previusState;
    }
}

public enum PlayerStates
{
    Attack,
    Interact,
    Death
}