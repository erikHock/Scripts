using System.Collections;
using System.Collections.Generic;
using UnityEngine;

[RequireComponent(typeof(BasicEnemyAI))]
public class LineOfSight : MonoBehaviour
{
    [SerializeField] float _sensorRadius;
    [SerializeField] float _maxSpeed;
    [SerializeField] float _acceleration;

    [SerializeField] LayerMask _playerLayer;
    private Transform _player;
    private BasicEnemyAI _enemyAI;

    public float _currentSpeed { get; private set; }
    public bool _isPlayerInRange { get; private set; } = false;

    private void Awake()
    {
        _enemyAI = GetComponent<BasicEnemyAI>();
    }

    private void Start()
    {
        _player = PlayerStateMachine.Instance.gameObject.transform;
    }
    void Update()
    {
        if (_enemyAI.GetCurrentState() == BasicEnemyAIStates.Death)
        {
            return;
        }

        if (PlayerStateMachine.Instance.GetCurrentState() == PlayerStates.Death)
        {
            _enemyAI.ChangeEnemyAIState(BasicEnemyAIStates.Idle);
            return;
        }

        // If player is in radius
        if (Physics.CheckSphere(transform.position, _sensorRadius, _playerLayer))
        {
            // Follow the player
            Vector3 dir = (_player.position - transform.position);
            float distance = Vector3.Distance(_player.position, transform.position);
            transform.LookAt(_player.position);

            _enemyAI.ChangeEnemyAIState(BasicEnemyAIStates.Follow);


            Vector3 startPos = new Vector3(transform.position.x, transform.position.y + 0.5f, transform.position.z);

            if (Physics.Raycast(startPos, transform.forward, 0.7f, _playerLayer))
            {
                _currentSpeed = Mathf.Lerp(_currentSpeed, 0f, 2f * Time.deltaTime);

                if (_currentSpeed < 0.1)
                {
                    _currentSpeed = 0f;

                    _enemyAI.ChangeEnemyAIState(BasicEnemyAIStates.Attack);
                }
            }
            else
            {
                _isPlayerInRange = false;

                _currentSpeed = Mathf.Lerp(_currentSpeed, _maxSpeed, 2f * Time.deltaTime);

                if (_currentSpeed > 0.9)
                {
                    _currentSpeed = 1f;

                    _enemyAI.ChangeEnemyAIState(BasicEnemyAIStates.Follow);
                }
            }

            if (distance < (distance / 100) * 30)
            {
                transform.position += dir * (_currentSpeed + _acceleration) * Time.deltaTime;
            }
            else 
            {
                transform.position += dir * _currentSpeed * Time.deltaTime;
            }
            
        }
            
    }

    public BasicEnemyAI GetBasicEnemyAI()
    {
        return _enemyAI;
    }

    private void OnDrawGizmos()
    {
        Gizmos.color = Color.red;
        Gizmos.DrawWireSphere(transform.position, _sensorRadius);

        Vector3 startPos = new Vector3(transform.position.x, transform.position.y + 0.5f, transform.position.z);
        Gizmos.DrawRay(startPos, transform.forward * 0.7f);
    }

    
}

