using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System;

public class ChestInteraction : MonoBehaviour
{
    private bool _isLootable = true;
    private void OnTriggerEnter(Collider other)
    {
        if (other.TryGetComponent<PlayerMovement>(out PlayerMovement player))
        {
            if (_isLootable)
            {
                PlayerStateMachine.Instance.ChangePlayerState(PlayerStates.Interact);
            }
        }
    }

    private void OnEnable()
    {
        PlayerStateMachine.Instance.OnInteractEnd += SetChestUnlootable;
    }

    private void OnDisable()
    {
        PlayerStateMachine.Instance.OnInteractEnd -= SetChestUnlootable;
    }

    private void SetChestUnlootable()
    {
        _isLootable = false;
    }


}
