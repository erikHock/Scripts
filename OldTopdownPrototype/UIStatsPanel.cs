using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using TMPro;

public class UIStatsPanel : MonoBehaviour
{
    [SerializeField] TextMeshProUGUI _weaponDamage;
    private void OnEnable()
    {
        PlayerStats.OnPlayerStatsChanged += SetPlayerStatsVisual;
    }

    private void OnDisable()
    {
        PlayerStats.OnPlayerStatsChanged -= SetPlayerStatsVisual;
    }

    private void SetPlayerStatsVisual(Stats playerStats)
    {
        _weaponDamage.text = $"Weapon Damage : {playerStats.weaponDamage}";
    }
}
