using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

[CreateAssetMenu(menuName = "ScriptableObjects/CardSO")]
public class CardSO : ScriptableObject
{
    [Range(1, 3)] public int rarity;
    [TextArea] public string details;
    public string header;

    public DamageType damageType;
    public float damageValue;
    
}

public enum DamageType
{
    WeaponDamage
}