using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class EnemyDamage : MonoBehaviour
{
    [SerializeField] float _damage = 10f;
    private Health _health;

    private void Start()
    {
        _health = PlayerStateMachine.Instance.gameObject.GetComponent<Health>();
    }
    public void DoDamage()
    {
        _health.SubtractHealth(_damage);
    }
}
