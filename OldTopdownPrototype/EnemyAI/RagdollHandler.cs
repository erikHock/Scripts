using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System.Linq;

public class RagdollHandler : MonoBehaviour
{
    [SerializeField] Animator _animator;
    [SerializeField] float _forceStrength = 50f;

    private Vector3 _forcePosition = Vector3.zero;
    private Rigidbody[] _rigidbodies;

    private void Awake()
    {
        _rigidbodies = GetComponentsInChildren<Rigidbody>();
        DisableRagdoll();
    }

    public void EnableRagdoll()
    {
        _animator.enabled = false;

        foreach (var rigidbody in _rigidbodies)
        {
            rigidbody.isKinematic = false;
        }

    }

    public void DisableRagdoll()
    {
        foreach (var rigidbody in _rigidbodies)
        {
            rigidbody.isKinematic = true;
        }

        _animator.enabled = true;
    }

    public void SetForce(Vector3 force,Vector3 hitPoint)
    {
        Rigidbody hitRigidbody = _rigidbodies.OrderBy(rigidbody => Vector3.Distance(rigidbody.position, hitPoint)).First();

        hitRigidbody.AddForceAtPosition(force, hitPoint, ForceMode.Impulse);
    }

    private void GetBulletDamagePosition(Vector3 position)
    {
        _forcePosition = position;
    }

    public void TriggerRagdoll()
    {
        Vector3 forcePosition = Vector3.one;
        EnableRagdoll();
        SetForce(transform.forward * _forceStrength, forcePosition);
    }

    private void OnEnable()
    {
        BulletDamage.OnBulletDamagePosition += GetBulletDamagePosition;
    }

    private void OnDisable()
    {
        BulletDamage.OnBulletDamagePosition -= GetBulletDamagePosition;
    }
}
