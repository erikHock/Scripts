using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System;

public class PlayerStats : MonoBehaviour
{
    private Stats playerStats;

    public static Action<Stats> OnPlayerStatsChanged;

    private void Awake()
    {
        playerStats.weaponDamage = 1;
    }
    private void Start()
    {
        OnPlayerStatsChanged?.Invoke(playerStats);
    }
    private void OnEnable()
    {
        CardSOHolder.OnCardChoosed += ModifyPlayerStats;
    }

    private void OnDisable()
    {
        CardSOHolder.OnCardChoosed -= ModifyPlayerStats;
    }

    private void ModifyPlayerStats(CardSO cardSO)
    {
        playerStats.weaponDamage += cardSO.damageValue;

        OnPlayerStatsChanged?.Invoke(playerStats);
    }
}
public struct Stats
{
    public float weaponDamage;
}