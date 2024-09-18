using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System;

public class Health : MonoBehaviour
{
    [SerializeField] private HealthBar _healthBar;
    [SerializeField] private float _maxHealth = 100f;
    [SerializeField] private bool _isPlayer = false;
    [SerializeField] private BasicEnemyAI _enemyAI;

    private float _currentHealth;
    private bool isDeath = false;

    private void Awake()
    {
        _currentHealth = _maxHealth;
    }

    private void Start()
    {
        _healthBar.SetSliderMaxValue(_maxHealth);
        _healthBar.SetSliderCurrentValue(_maxHealth);
    }

    private void AddHealth(float amount)
    {
        if (!isDeath)
        {
            if (_currentHealth + amount >= _maxHealth)
            {
                _currentHealth = _maxHealth;
            }
            else if (_currentHealth + amount < _maxHealth)
            {
                _currentHealth += amount;
            }
            _healthBar.SetSliderCurrentValue(_currentHealth);
        }

    }

    public void SubtractHealth(float amount)
    {
        if (_currentHealth - amount <= 0f && !isDeath)
        {
            _currentHealth = 0f;
            
            isDeath = true;

            if (_isPlayer)
            {
                PlayerStateMachine.Instance.ChangePlayerState(PlayerStates.Death);
            }
            else
            {
                if (_enemyAI != null) { _enemyAI.ChangeEnemyAIState(BasicEnemyAIStates.Death); }

            }
        }
        else if (_currentHealth - amount > 0f)
        {
            _currentHealth -= amount;
        }

        _healthBar.SetSliderCurrentValue(_currentHealth);
    }

    private void IncreaseHealth(float amount)
    {
        _maxHealth += amount;

        _healthBar.SetSliderMaxValue(_maxHealth);
    }
    private void DecreaseHealth(float amount)
    {
        _maxHealth -= amount;

        _healthBar.SetSliderMaxValue(_maxHealth);
    }

    public bool IsPlayer()
    {
        return _isPlayer;
    }

    public bool IsDeath()
    { 
        return isDeath;
    }
    
}
