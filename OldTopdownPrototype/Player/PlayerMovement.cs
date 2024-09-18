using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System;

public class PlayerMovement : MonoBehaviour
{
    [SerializeField] private float _speed = 5f;
    [SerializeField] private float _rotationSpeed = 5f;
    [SerializeField] private Transform _playerVisual;

    public static Action<bool> OnPlayerMove;
    public Vector3 movementDir { get; private set; }
    void Update()
    {
        if (PlayerStateMachine.Instance.GetCurrentState() != PlayerStates.Attack) return;

        Vector3 inputDir = Vector3.zero;

        if (Input.GetKey(KeyCode.W))
        {
            inputDir.z = 1f;
        }

        if (Input.GetKey(KeyCode.S))
        {
            inputDir.z = -1f;
        }

        if (Input.GetKey(KeyCode.A))
        {
            inputDir.x = -1f;
        }

        if (Input.GetKey(KeyCode.D))
        {
            inputDir.x = 1f;
        }

        inputDir.Normalize();
        movementDir = inputDir;

        if (inputDir.x != 0f || inputDir.z != 0f)
        {
            transform.position += inputDir * Time.deltaTime * _speed;
            
            _playerVisual.rotation = Quaternion.RotateTowards(_playerVisual.rotation,Quaternion.LookRotation(inputDir),360 * Time.deltaTime * _rotationSpeed);
            
            OnPlayerMove?.Invoke(true);
        }
        else
        {
            OnPlayerMove?.Invoke(false);
        }

    }
   
}
