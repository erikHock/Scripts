using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System;

public class BulletDamage : MonoBehaviour
{
    [SerializeField] private float _damage = 10f;
        
    public static Action<Vector3> OnBulletDamagePosition;
    
    private void OnCollisionEnter(Collision collision)
    {
        OnBulletDamagePosition?.Invoke(collision.GetContact(0).point);

        var health = collision.gameObject.GetComponentInParent<Health>();

        if (health != null && !health.IsPlayer())
        {
            health.SubtractHealth(_damage);
        }
        Debug.Log(collision.gameObject.name);
        Destroy(this.gameObject);        
    }
}
